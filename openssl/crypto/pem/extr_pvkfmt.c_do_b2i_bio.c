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
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int BIO_read (int /*<<< orphan*/ *,unsigned char*,unsigned int) ; 
 unsigned int BLOB_MAX_LENGTH ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 unsigned char* OPENSSL_malloc (unsigned int) ; 
 int /*<<< orphan*/  PEM_F_DO_B2I_BIO ; 
 int /*<<< orphan*/  PEM_R_HEADER_TOO_LONG ; 
 int /*<<< orphan*/  PEM_R_KEYBLOB_TOO_SHORT ; 
 int /*<<< orphan*/  PEMerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * b2i_dss (unsigned char const**,unsigned int,int) ; 
 int /*<<< orphan*/ * b2i_rsa (unsigned char const**,unsigned int,int) ; 
 unsigned int blob_length (unsigned int,int,int) ; 
 scalar_t__ do_blob_header (unsigned char const**,int,unsigned int*,unsigned int*,int*,int*) ; 

__attribute__((used)) static EVP_PKEY *do_b2i_bio(BIO *in, int ispub)
{
    const unsigned char *p;
    unsigned char hdr_buf[16], *buf = NULL;
    unsigned int bitlen, magic, length;
    int isdss;
    EVP_PKEY *ret = NULL;
    if (BIO_read(in, hdr_buf, 16) != 16) {
        PEMerr(PEM_F_DO_B2I_BIO, PEM_R_KEYBLOB_TOO_SHORT);
        return NULL;
    }
    p = hdr_buf;
    if (do_blob_header(&p, 16, &magic, &bitlen, &isdss, &ispub) <= 0)
        return NULL;

    length = blob_length(bitlen, isdss, ispub);
    if (length > BLOB_MAX_LENGTH) {
        PEMerr(PEM_F_DO_B2I_BIO, PEM_R_HEADER_TOO_LONG);
        return NULL;
    }
    buf = OPENSSL_malloc(length);
    if (buf == NULL) {
        PEMerr(PEM_F_DO_B2I_BIO, ERR_R_MALLOC_FAILURE);
        goto err;
    }
    p = buf;
    if (BIO_read(in, buf, length) != (int)length) {
        PEMerr(PEM_F_DO_B2I_BIO, PEM_R_KEYBLOB_TOO_SHORT);
        goto err;
    }

    if (isdss)
        ret = b2i_dss(&p, bitlen, ispub);
    else
        ret = b2i_rsa(&p, bitlen, ispub);

 err:
    OPENSSL_free(buf);
    return ret;
}