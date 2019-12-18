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
typedef  int /*<<< orphan*/  EVP_PKEY_CTX ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;
typedef  int /*<<< orphan*/  EVP_MD ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*) ; 
 int BIO_read (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int EVP_DigestSign (int /*<<< orphan*/ *,unsigned char*,size_t*,unsigned char*,int) ; 
 int EVP_DigestSignFinal (int /*<<< orphan*/ *,unsigned char*,size_t*) ; 
 int EVP_DigestSignInit (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int EVP_DigestSignUpdate (int /*<<< orphan*/ *,unsigned char*,size_t) ; 
 int EVP_DigestVerify (int /*<<< orphan*/ *,unsigned char*,size_t,unsigned char*,int) ; 
 int EVP_DigestVerifyFinal (int /*<<< orphan*/ *,unsigned char*,size_t) ; 
 int EVP_DigestVerifyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int EVP_DigestVerifyUpdate (int /*<<< orphan*/ *,unsigned char*,size_t) ; 
 int /*<<< orphan*/  EVP_MD_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_MD_CTX_new () ; 
 int /*<<< orphan*/  EVP_MD_CTX_set_pkey_ctx (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ EVP_PKEY_ED25519 ; 
 scalar_t__ EVP_PKEY_ED448 ; 
#define  EVP_PKEY_OP_SIGN 129 
#define  EVP_PKEY_OP_VERIFY 128 
 scalar_t__ EVP_PKEY_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OPENSSL_free (unsigned char*) ; 
 int TBUF_MAXSIZE ; 
 unsigned char* app_malloc (size_t,char*) ; 
 int /*<<< orphan*/  bio_err ; 

__attribute__((used)) static int do_raw_keyop(int pkey_op, EVP_PKEY_CTX *ctx,
                        const EVP_MD *md, EVP_PKEY *pkey, BIO *in,
                        int filesize, unsigned char *sig, int siglen,
                        unsigned char **out, size_t *poutlen)
{
    int rv = 0;
    EVP_MD_CTX *mctx = NULL;
    unsigned char tbuf[TBUF_MAXSIZE];
    unsigned char *mbuf = NULL;
    int buf_len = 0;

    if ((mctx = EVP_MD_CTX_new()) == NULL) {
        BIO_printf(bio_err, "Error: out of memory\n");
        return rv;
    }
    EVP_MD_CTX_set_pkey_ctx(mctx, ctx);

    /* Some algorithms only support oneshot digests */
    if (EVP_PKEY_id(pkey) == EVP_PKEY_ED25519
            || EVP_PKEY_id(pkey) == EVP_PKEY_ED448) {
        if (filesize < 0) {
            BIO_printf(bio_err,
                       "Error: unable to determine file size for oneshot operation\n");
            goto end;
        }
        mbuf = app_malloc(filesize, "oneshot sign/verify buffer");
        switch(pkey_op) {
        case EVP_PKEY_OP_VERIFY:
            if (EVP_DigestVerifyInit(mctx, NULL, md, NULL, pkey) != 1)
                goto end;
            buf_len = BIO_read(in, mbuf, filesize);
            if (buf_len != filesize) {
                BIO_printf(bio_err, "Error reading raw input data\n");
                goto end;
            }
            rv = EVP_DigestVerify(mctx, sig, (size_t)siglen, mbuf, buf_len);
            break;
        case EVP_PKEY_OP_SIGN:
            if (EVP_DigestSignInit(mctx, NULL, md, NULL, pkey) != 1)
                goto end;
            buf_len = BIO_read(in, mbuf, filesize);
            if (buf_len != filesize) {
                BIO_printf(bio_err, "Error reading raw input data\n");
                goto end;
            }
            rv = EVP_DigestSign(mctx, NULL, poutlen, mbuf, buf_len);
            if (rv == 1 && out != NULL) {
                *out = app_malloc(*poutlen, "buffer output");
                rv = EVP_DigestSign(mctx, *out, poutlen, mbuf, buf_len);
            }
            break;
        }
        goto end;
    }

    switch(pkey_op) {
    case EVP_PKEY_OP_VERIFY:
        if (EVP_DigestVerifyInit(mctx, NULL, md, NULL, pkey) != 1)
            goto end;
        for (;;) {
            buf_len = BIO_read(in, tbuf, TBUF_MAXSIZE);
            if (buf_len == 0)
                break;
            if (buf_len < 0) {
                BIO_printf(bio_err, "Error reading raw input data\n");
                goto end;
            }
            rv = EVP_DigestVerifyUpdate(mctx, tbuf, (size_t)buf_len);
            if (rv != 1) {
                BIO_printf(bio_err, "Error verifying raw input data\n");
                goto end;
            }
        }
        rv = EVP_DigestVerifyFinal(mctx, sig, (size_t)siglen);
        break;
    case EVP_PKEY_OP_SIGN:
        if (EVP_DigestSignInit(mctx, NULL, md, NULL, pkey) != 1)
            goto end;
        for (;;) {
            buf_len = BIO_read(in, tbuf, TBUF_MAXSIZE);
            if (buf_len == 0)
                break;
            if (buf_len < 0) {
                BIO_printf(bio_err, "Error reading raw input data\n");
                goto end;
            }
            rv = EVP_DigestSignUpdate(mctx, tbuf, (size_t)buf_len);
            if (rv != 1) {
                BIO_printf(bio_err, "Error signing raw input data\n");
                goto end;
            }
        }
        rv = EVP_DigestSignFinal(mctx, NULL, poutlen);
        if (rv == 1 && out != NULL) {
            *out = app_malloc(*poutlen, "buffer output");
            rv = EVP_DigestSignFinal(mctx, *out, poutlen);
        }
        break;
    }

 end:
    OPENSSL_free(mbuf);
    EVP_MD_CTX_free(mctx);
    return rv;
}