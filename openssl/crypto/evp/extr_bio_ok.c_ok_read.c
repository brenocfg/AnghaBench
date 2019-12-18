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
struct TYPE_3__ {int buf_len; int buf_off; int buf_len_save; size_t buf_off_save; int sigio; scalar_t__ cont; int /*<<< orphan*/ * buf; scalar_t__ blockout; } ;
typedef  TYPE_1__ BIO_OK_CTX ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_clear_retry_flags (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_copy_next_retry (int /*<<< orphan*/ *) ; 
 TYPE_1__* BIO_get_data (int /*<<< orphan*/ *) ; 
 scalar_t__ BIO_get_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_next (int /*<<< orphan*/ *) ; 
 int BIO_read (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int IOBS ; 
 int /*<<< orphan*/  block_in (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sig_in (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ok_read(BIO *b, char *out, int outl)
{
    int ret = 0, i, n;
    BIO_OK_CTX *ctx;
    BIO *next;

    if (out == NULL)
        return 0;

    ctx = BIO_get_data(b);
    next = BIO_next(b);

    if ((ctx == NULL) || (next == NULL) || (BIO_get_init(b) == 0))
        return 0;

    while (outl > 0) {

        /* copy clean bytes to output buffer */
        if (ctx->blockout) {
            i = ctx->buf_len - ctx->buf_off;
            if (i > outl)
                i = outl;
            memcpy(out, &(ctx->buf[ctx->buf_off]), i);
            ret += i;
            out += i;
            outl -= i;
            ctx->buf_off += i;

            /* all clean bytes are out */
            if (ctx->buf_len == ctx->buf_off) {
                ctx->buf_off = 0;

                /*
                 * copy start of the next block into proper place
                 */
                if (ctx->buf_len_save - ctx->buf_off_save > 0) {
                    ctx->buf_len = ctx->buf_len_save - ctx->buf_off_save;
                    memmove(ctx->buf, &(ctx->buf[ctx->buf_off_save]),
                            ctx->buf_len);
                } else {
                    ctx->buf_len = 0;
                }
                ctx->blockout = 0;
            }
        }

        /* output buffer full -- cancel */
        if (outl == 0)
            break;

        /* no clean bytes in buffer -- fill it */
        n = IOBS - ctx->buf_len;
        i = BIO_read(next, &(ctx->buf[ctx->buf_len]), n);

        if (i <= 0)
            break;              /* nothing new */

        ctx->buf_len += i;

        /* no signature yet -- check if we got one */
        if (ctx->sigio == 1) {
            if (!sig_in(b)) {
                BIO_clear_retry_flags(b);
                return 0;
            }
        }

        /* signature ok -- check if we got block */
        if (ctx->sigio == 0) {
            if (!block_in(b)) {
                BIO_clear_retry_flags(b);
                return 0;
            }
        }

        /* invalid block -- cancel */
        if (ctx->cont <= 0)
            break;

    }

    BIO_clear_retry_flags(b);
    BIO_copy_next_retry(b);
    return ret;
}