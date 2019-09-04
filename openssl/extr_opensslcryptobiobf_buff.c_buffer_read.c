#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * next_bio; scalar_t__ ptr; } ;
struct TYPE_6__ {int ibuf_len; char* ibuf; size_t ibuf_off; int ibuf_size; } ;
typedef  TYPE_1__ BIO_F_BUFFER_CTX ;
typedef  TYPE_2__ BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_clear_retry_flags (TYPE_2__*) ; 
 int /*<<< orphan*/  BIO_copy_next_retry (TYPE_2__*) ; 
 int BIO_read (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 

__attribute__((used)) static int buffer_read(BIO *b, char *out, int outl)
{
    int i, num = 0;
    BIO_F_BUFFER_CTX *ctx;

    if (out == NULL)
        return 0;
    ctx = (BIO_F_BUFFER_CTX *)b->ptr;

    if ((ctx == NULL) || (b->next_bio == NULL))
        return 0;
    num = 0;
    BIO_clear_retry_flags(b);

 start:
    i = ctx->ibuf_len;
    /* If there is stuff left over, grab it */
    if (i != 0) {
        if (i > outl)
            i = outl;
        memcpy(out, &(ctx->ibuf[ctx->ibuf_off]), i);
        ctx->ibuf_off += i;
        ctx->ibuf_len -= i;
        num += i;
        if (outl == i)
            return num;
        outl -= i;
        out += i;
    }

    /*
     * We may have done a partial read. try to do more. We have nothing in
     * the buffer. If we get an error and have read some data, just return it
     * and let them retry to get the error again. copy direct to parent
     * address space
     */
    if (outl > ctx->ibuf_size) {
        for (;;) {
            i = BIO_read(b->next_bio, out, outl);
            if (i <= 0) {
                BIO_copy_next_retry(b);
                if (i < 0)
                    return ((num > 0) ? num : i);
                if (i == 0)
                    return num;
            }
            num += i;
            if (outl == i)
                return num;
            out += i;
            outl -= i;
        }
    }
    /* else */

    /* we are going to be doing some buffering */
    i = BIO_read(b->next_bio, ctx->ibuf, ctx->ibuf_size);
    if (i <= 0) {
        BIO_copy_next_retry(b);
        if (i < 0)
            return ((num > 0) ? num : i);
        if (i == 0)
            return num;
    }
    ctx->ibuf_off = 0;
    ctx->ibuf_len = i;

    /* Lets re-read using ourselves :-) */
    goto start;
}