#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  X509 ;
typedef  int /*<<< orphan*/  PKCS7 ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 scalar_t__ BIO_TYPE_CIPHER ; 
 int /*<<< orphan*/  BIO_f_buffer () ; 
 int /*<<< orphan*/  BIO_free_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_get_cipher_status (int /*<<< orphan*/ *) ; 
 scalar_t__ BIO_method_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * BIO_push (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int BIO_read (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int BIO_write (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  BUFFERSIZE ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OPENSSL_free (char*) ; 
 char* OPENSSL_malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PKCS7_F_PKCS7_DECRYPT ; 
 int /*<<< orphan*/  PKCS7_R_DECRYPT_ERROR ; 
 int /*<<< orphan*/  PKCS7_R_INVALID_NULL_POINTER ; 
 int /*<<< orphan*/  PKCS7_R_PRIVATE_KEY_DOES_NOT_MATCH_CERTIFICATE ; 
 int /*<<< orphan*/  PKCS7_R_WRONG_CONTENT_TYPE ; 
 int PKCS7_TEXT ; 
 int /*<<< orphan*/ * PKCS7_dataDecode (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PKCS7_type_is_enveloped (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PKCS7err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SMIME_text (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_check_private_key (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int PKCS7_decrypt(PKCS7 *p7, EVP_PKEY *pkey, X509 *cert, BIO *data, int flags)
{
    BIO *tmpmem;
    int ret = 0, i;
    char *buf = NULL;

    if (p7 == NULL) {
        PKCS7err(PKCS7_F_PKCS7_DECRYPT, PKCS7_R_INVALID_NULL_POINTER);
        return 0;
    }

    if (!PKCS7_type_is_enveloped(p7)) {
        PKCS7err(PKCS7_F_PKCS7_DECRYPT, PKCS7_R_WRONG_CONTENT_TYPE);
        return 0;
    }

    if (cert && !X509_check_private_key(cert, pkey)) {
        PKCS7err(PKCS7_F_PKCS7_DECRYPT,
                 PKCS7_R_PRIVATE_KEY_DOES_NOT_MATCH_CERTIFICATE);
        return 0;
    }

    if ((tmpmem = PKCS7_dataDecode(p7, pkey, NULL, cert)) == NULL) {
        PKCS7err(PKCS7_F_PKCS7_DECRYPT, PKCS7_R_DECRYPT_ERROR);
        return 0;
    }

    if (flags & PKCS7_TEXT) {
        BIO *tmpbuf, *bread;
        /* Encrypt BIOs can't do BIO_gets() so add a buffer BIO */
        if ((tmpbuf = BIO_new(BIO_f_buffer())) == NULL) {
            PKCS7err(PKCS7_F_PKCS7_DECRYPT, ERR_R_MALLOC_FAILURE);
            BIO_free_all(tmpmem);
            return 0;
        }
        if ((bread = BIO_push(tmpbuf, tmpmem)) == NULL) {
            PKCS7err(PKCS7_F_PKCS7_DECRYPT, ERR_R_MALLOC_FAILURE);
            BIO_free_all(tmpbuf);
            BIO_free_all(tmpmem);
            return 0;
        }
        ret = SMIME_text(bread, data);
        if (ret > 0 && BIO_method_type(tmpmem) == BIO_TYPE_CIPHER) {
            if (!BIO_get_cipher_status(tmpmem))
                ret = 0;
        }
        BIO_free_all(bread);
        return ret;
    }
    if ((buf = OPENSSL_malloc(BUFFERSIZE)) == NULL) {
        PKCS7err(PKCS7_F_PKCS7_DECRYPT, ERR_R_MALLOC_FAILURE);
        goto err;
    }
    for (;;) {
        i = BIO_read(tmpmem, buf, BUFFERSIZE);
        if (i <= 0) {
            ret = 1;
            if (BIO_method_type(tmpmem) == BIO_TYPE_CIPHER) {
                if (!BIO_get_cipher_status(tmpmem))
                    ret = 0;
            }

            break;
        }
        if (BIO_write(data, buf, i) != i) {
            break;
        }
    }
err:
    OPENSSL_free(buf);
    BIO_free_all(tmpmem);
    return ret;
}