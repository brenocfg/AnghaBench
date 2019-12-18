#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t buf_len; size_t buf_off; scalar_t__ cont; int /*<<< orphan*/ * buf; scalar_t__ sigio; int /*<<< orphan*/ * md; } ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;
typedef  int /*<<< orphan*/  EVP_MD ;
typedef  TYPE_1__ BIO_OK_CTX ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_clear_retry_flags (int /*<<< orphan*/ *) ; 
 TYPE_1__* BIO_get_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_DigestFinal_ex (int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_DigestInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_DigestUpdate (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EVP_MAX_MD_SIZE ; 
 int /*<<< orphan*/ * EVP_MD_CTX_md (int /*<<< orphan*/ *) ; 
 void* EVP_MD_CTX_md_data (int /*<<< orphan*/ *) ; 
 int EVP_MD_size (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  WELLKNOWN ; 
 int /*<<< orphan*/  longswap (void*,int) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sig_in(BIO *b)
{
    BIO_OK_CTX *ctx;
    EVP_MD_CTX *md;
    unsigned char tmp[EVP_MAX_MD_SIZE];
    int ret = 0;
    const EVP_MD *digest;
    int md_size;
    void *md_data;

    ctx = BIO_get_data(b);
    md = ctx->md;
    digest = EVP_MD_CTX_md(md);
    md_size = EVP_MD_size(digest);
    md_data = EVP_MD_CTX_md_data(md);

    if ((int)(ctx->buf_len - ctx->buf_off) < 2 * md_size)
        return 1;

    if (!EVP_DigestInit_ex(md, digest, NULL))
        goto berr;
    memcpy(md_data, &(ctx->buf[ctx->buf_off]), md_size);
    longswap(md_data, md_size);
    ctx->buf_off += md_size;

    if (!EVP_DigestUpdate(md, WELLKNOWN, strlen(WELLKNOWN)))
        goto berr;
    if (!EVP_DigestFinal_ex(md, tmp, NULL))
        goto berr;
    ret = memcmp(&(ctx->buf[ctx->buf_off]), tmp, md_size) == 0;
    ctx->buf_off += md_size;
    if (ret == 1) {
        ctx->sigio = 0;
        if (ctx->buf_len != ctx->buf_off) {
            memmove(ctx->buf, &(ctx->buf[ctx->buf_off]),
                    ctx->buf_len - ctx->buf_off);
        }
        ctx->buf_len -= ctx->buf_off;
        ctx->buf_off = 0;
    } else {
        ctx->cont = 0;
    }
    return 1;
 berr:
    BIO_clear_retry_flags(b);
    return 0;
}