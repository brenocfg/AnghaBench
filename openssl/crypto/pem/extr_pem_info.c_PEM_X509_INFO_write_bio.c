#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pem_password_cb ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_5__ {unsigned char* iv; int /*<<< orphan*/ * cipher; } ;
struct TYPE_7__ {int enc_len; int /*<<< orphan*/ * x509; TYPE_2__* x_pkey; TYPE_1__ enc_cipher; int /*<<< orphan*/ * enc_data; } ;
typedef  TYPE_3__ X509_INFO ;
struct TYPE_6__ {int /*<<< orphan*/  dec_pkey; } ;
typedef  int /*<<< orphan*/  EVP_CIPHER ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int EVP_CIPHER_iv_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_CIPHER_nid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_PKEY_get0_RSA (int /*<<< orphan*/ ) ; 
 char* OBJ_nid2sn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_cleanse (char*,int) ; 
 int PEM_BUFSIZE ; 
 int /*<<< orphan*/  PEM_F_PEM_X509_INFO_WRITE_BIO ; 
 int /*<<< orphan*/  PEM_R_CIPHER_IS_NULL ; 
 int /*<<< orphan*/  PEM_R_UNSUPPORTED_CIPHER ; 
 int /*<<< orphan*/  PEM_STRING_RSA ; 
 int /*<<< orphan*/  PEM_TYPE_ENCRYPTED ; 
 int /*<<< orphan*/  PEM_dek_info (char*,char const*,int,char*) ; 
 int /*<<< orphan*/  PEM_proc_type (char*,int /*<<< orphan*/ ) ; 
 int PEM_write_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,unsigned char*,int) ; 
 scalar_t__ PEM_write_bio_RSAPrivateKey (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned char*,int,int /*<<< orphan*/ *,void*) ; 
 scalar_t__ PEM_write_bio_X509 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PEMerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 

int PEM_X509_INFO_write_bio(BIO *bp, X509_INFO *xi, EVP_CIPHER *enc,
                            unsigned char *kstr, int klen,
                            pem_password_cb *cb, void *u)
{
    int i, ret = 0;
    unsigned char *data = NULL;
    const char *objstr = NULL;
    char buf[PEM_BUFSIZE];
    unsigned char *iv = NULL;

    if (enc != NULL) {
        objstr = OBJ_nid2sn(EVP_CIPHER_nid(enc));
        if (objstr == NULL
                   /*
                    * Check "Proc-Type: 4,Encrypted\nDEK-Info: objstr,hex-iv\n"
                    * fits into buf
                    */
                || (strlen(objstr) + 23 + 2 * EVP_CIPHER_iv_length(enc) + 13)
                   > sizeof(buf)) {
            PEMerr(PEM_F_PEM_X509_INFO_WRITE_BIO, PEM_R_UNSUPPORTED_CIPHER);
            goto err;
        }
    }

    /*
     * now for the fun part ... if we have a private key then we have to be
     * able to handle a not-yet-decrypted key being written out correctly ...
     * if it is decrypted or it is non-encrypted then we use the base code
     */
    if (xi->x_pkey != NULL) {
        if ((xi->enc_data != NULL) && (xi->enc_len > 0)) {
            if (enc == NULL) {
                PEMerr(PEM_F_PEM_X509_INFO_WRITE_BIO, PEM_R_CIPHER_IS_NULL);
                goto err;
            }

            /* copy from weirdo names into more normal things */
            iv = xi->enc_cipher.iv;
            data = (unsigned char *)xi->enc_data;
            i = xi->enc_len;

            /*
             * we take the encryption data from the internal stuff rather
             * than what the user has passed us ... as we have to match
             * exactly for some strange reason
             */
            objstr = OBJ_nid2sn(EVP_CIPHER_nid(xi->enc_cipher.cipher));
            if (objstr == NULL) {
                PEMerr(PEM_F_PEM_X509_INFO_WRITE_BIO,
                       PEM_R_UNSUPPORTED_CIPHER);
                goto err;
            }

            /* Create the right magic header stuff */
            buf[0] = '\0';
            PEM_proc_type(buf, PEM_TYPE_ENCRYPTED);
            PEM_dek_info(buf, objstr, EVP_CIPHER_iv_length(enc),
                         (char *)iv);

            /* use the normal code to write things out */
            i = PEM_write_bio(bp, PEM_STRING_RSA, buf, data, i);
            if (i <= 0)
                goto err;
        } else {
            /* Add DSA/DH */
#ifndef OPENSSL_NO_RSA
            /* normal optionally encrypted stuff */
            if (PEM_write_bio_RSAPrivateKey(bp,
                                            EVP_PKEY_get0_RSA(xi->x_pkey->dec_pkey),
                                            enc, kstr, klen, cb, u) <= 0)
                goto err;
#endif
        }
    }

    /* if we have a certificate then write it out now */
    if ((xi->x509 != NULL) && (PEM_write_bio_X509(bp, xi->x509) <= 0))
        goto err;

    /*
     * we are ignoring anything else that is loaded into the X509_INFO
     * structure for the moment ... as I don't need it so I'm not coding it
     * here and Eric can do it when this makes it into the base library --tjh
     */

    ret = 1;

 err:
    OPENSSL_cleanse(buf, PEM_BUFSIZE);
    return ret;
}