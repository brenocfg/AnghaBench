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
struct TYPE_3__ {int buf_len; int buf_off; int /*<<< orphan*/ * buf; scalar_t__ blockout; scalar_t__ cont; scalar_t__ sigio; } ;
typedef  TYPE_1__ BIO_OK_CTX ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_clear_retry_flags (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_copy_next_retry (int /*<<< orphan*/ *) ; 
 TYPE_1__* BIO_get_data (int /*<<< orphan*/ *) ; 
 scalar_t__ BIO_get_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_should_retry (int /*<<< orphan*/ *) ; 
 int BIO_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int OK_BLOCK_BLOCK ; 
 int OK_BLOCK_SIZE ; 
 int /*<<< orphan*/  block_out (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  sig_out (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ok_write(BIO *b, const char *in, int inl)
{
    int ret = 0, n, i;
    BIO_OK_CTX *ctx;
    BIO *next;

    if (inl <= 0)
        return inl;

    ctx = BIO_get_data(b);
    next = BIO_next(b);
    ret = inl;

    if ((ctx == NULL) || (next == NULL) || (BIO_get_init(b) == 0))
        return 0;

    if (ctx->sigio && !sig_out(b))
        return 0;

    do {
        BIO_clear_retry_flags(b);
        n = ctx->buf_len - ctx->buf_off;
        while (ctx->blockout && n > 0) {
            i = BIO_write(next, &(ctx->buf[ctx->buf_off]), n);
            if (i <= 0) {
                BIO_copy_next_retry(b);
                if (!BIO_should_retry(b))
                    ctx->cont = 0;
                return i;
            }
            ctx->buf_off += i;
            n -= i;
        }

        /* at this point all pending data has been written */
        ctx->blockout = 0;
        if (ctx->buf_len == ctx->buf_off) {
            ctx->buf_len = OK_BLOCK_BLOCK;
            ctx->buf_off = 0;
        }

        if ((in == NULL) || (inl <= 0))
            return 0;

        n = (inl + ctx->buf_len > OK_BLOCK_SIZE + OK_BLOCK_BLOCK) ?
            (int)(OK_BLOCK_SIZE + OK_BLOCK_BLOCK - ctx->buf_len) : inl;

        memcpy(&ctx->buf[ctx->buf_len], in, n);
        ctx->buf_len += n;
        inl -= n;
        in += n;

        if (ctx->buf_len >= OK_BLOCK_SIZE + OK_BLOCK_BLOCK) {
            if (!block_out(b)) {
                BIO_clear_retry_flags(b);
                return 0;
            }
        }
    } while (inl > 0);

    BIO_clear_retry_flags(b);
    BIO_copy_next_retry(b);
    return ret;
}