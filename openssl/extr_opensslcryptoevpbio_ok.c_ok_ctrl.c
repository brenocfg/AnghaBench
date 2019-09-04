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
struct TYPE_3__ {long buf_len; long buf_off; int cont; int finished; int sigio; int /*<<< orphan*/  md; int /*<<< orphan*/  blockout; int /*<<< orphan*/  buf_off_save; int /*<<< orphan*/  buf_len_save; } ;
typedef  int /*<<< orphan*/  EVP_MD ;
typedef  TYPE_1__ BIO_OK_CTX ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
#define  BIO_CTRL_EOF 136 
#define  BIO_CTRL_FLUSH 135 
#define  BIO_CTRL_INFO 134 
#define  BIO_CTRL_PENDING 133 
#define  BIO_CTRL_RESET 132 
#define  BIO_CTRL_WPENDING 131 
#define  BIO_C_DO_STATE_MACHINE 130 
#define  BIO_C_GET_MD 129 
#define  BIO_C_SET_MD 128 
 int /*<<< orphan*/  BIO_clear_retry_flags (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_copy_next_retry (int /*<<< orphan*/ *) ; 
 long BIO_ctrl (int /*<<< orphan*/ *,int,long,void*) ; 
 TYPE_1__* BIO_get_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_get_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_set_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  EVP_DigestInit_ex (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_MD_CTX_md (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  block_out (int /*<<< orphan*/ *) ; 
 int ok_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static long ok_ctrl(BIO *b, int cmd, long num, void *ptr)
{
    BIO_OK_CTX *ctx;
    EVP_MD *md;
    const EVP_MD **ppmd;
    long ret = 1;
    int i;
    BIO *next;

    ctx = BIO_get_data(b);
    next = BIO_next(b);

    switch (cmd) {
    case BIO_CTRL_RESET:
        ctx->buf_len = 0;
        ctx->buf_off = 0;
        ctx->buf_len_save = 0;
        ctx->buf_off_save = 0;
        ctx->cont = 1;
        ctx->finished = 0;
        ctx->blockout = 0;
        ctx->sigio = 1;
        ret = BIO_ctrl(next, cmd, num, ptr);
        break;
    case BIO_CTRL_EOF:         /* More to read */
        if (ctx->cont <= 0)
            ret = 1;
        else
            ret = BIO_ctrl(next, cmd, num, ptr);
        break;
    case BIO_CTRL_PENDING:     /* More to read in buffer */
    case BIO_CTRL_WPENDING:    /* More to read in buffer */
        ret = ctx->blockout ? ctx->buf_len - ctx->buf_off : 0;
        if (ret <= 0)
            ret = BIO_ctrl(next, cmd, num, ptr);
        break;
    case BIO_CTRL_FLUSH:
        /* do a final write */
        if (ctx->blockout == 0)
            if (!block_out(b))
                return 0;

        while (ctx->blockout) {
            i = ok_write(b, NULL, 0);
            if (i < 0) {
                ret = i;
                break;
            }
        }

        ctx->finished = 1;
        ctx->buf_off = ctx->buf_len = 0;
        ctx->cont = (int)ret;

        /* Finally flush the underlying BIO */
        ret = BIO_ctrl(next, cmd, num, ptr);
        break;
    case BIO_C_DO_STATE_MACHINE:
        BIO_clear_retry_flags(b);
        ret = BIO_ctrl(next, cmd, num, ptr);
        BIO_copy_next_retry(b);
        break;
    case BIO_CTRL_INFO:
        ret = (long)ctx->cont;
        break;
    case BIO_C_SET_MD:
        md = ptr;
        if (!EVP_DigestInit_ex(ctx->md, md, NULL))
            return 0;
        BIO_set_init(b, 1);
        break;
    case BIO_C_GET_MD:
        if (BIO_get_init(b)) {
            ppmd = ptr;
            *ppmd = EVP_MD_CTX_md(ctx->md);
        } else
            ret = 0;
        break;
    default:
        ret = BIO_ctrl(next, cmd, num, ptr);
        break;
    }
    return ret;
}