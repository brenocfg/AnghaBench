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
typedef  int /*<<< orphan*/  tl ;
struct TYPE_3__ {unsigned long* buf; unsigned long buf_len; unsigned long buf_off_save; unsigned long buf_len_save; int buf_off; int blockout; scalar_t__ cont; int /*<<< orphan*/ * md; } ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;
typedef  TYPE_1__ BIO_OK_CTX ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_clear_retry_flags (int /*<<< orphan*/ *) ; 
 TYPE_1__* BIO_get_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_DigestFinal_ex (int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_DigestUpdate (int /*<<< orphan*/ *,unsigned char*,unsigned long) ; 
 int EVP_MAX_MD_SIZE ; 
 int /*<<< orphan*/  EVP_MD_CTX_md (int /*<<< orphan*/ *) ; 
 int EVP_MD_size (int /*<<< orphan*/ ) ; 
 int OK_BLOCK_BLOCK ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ memcmp (unsigned long*,unsigned char*,int) ; 

__attribute__((used)) static int block_in(BIO *b)
{
    BIO_OK_CTX *ctx;
    EVP_MD_CTX *md;
    unsigned long tl = 0;
    unsigned char tmp[EVP_MAX_MD_SIZE];
    int md_size;

    ctx = BIO_get_data(b);
    md = ctx->md;
    md_size = EVP_MD_size(EVP_MD_CTX_md(md));

    assert(sizeof(tl) >= OK_BLOCK_BLOCK); /* always true */
    tl = ctx->buf[0];
    tl <<= 8;
    tl |= ctx->buf[1];
    tl <<= 8;
    tl |= ctx->buf[2];
    tl <<= 8;
    tl |= ctx->buf[3];

    if (ctx->buf_len < tl + OK_BLOCK_BLOCK + md_size)
        return 1;

    if (!EVP_DigestUpdate(md,
                          (unsigned char *)&(ctx->buf[OK_BLOCK_BLOCK]), tl))
        goto berr;
    if (!EVP_DigestFinal_ex(md, tmp, NULL))
        goto berr;
    if (memcmp(&(ctx->buf[tl + OK_BLOCK_BLOCK]), tmp, md_size) == 0) {
        /* there might be parts from next block lurking around ! */
        ctx->buf_off_save = tl + OK_BLOCK_BLOCK + md_size;
        ctx->buf_len_save = ctx->buf_len;
        ctx->buf_off = OK_BLOCK_BLOCK;
        ctx->buf_len = tl + OK_BLOCK_BLOCK;
        ctx->blockout = 1;
    } else {
        ctx->cont = 0;
    }
    return 1;
 berr:
    BIO_clear_retry_flags(b);
    return 0;
}