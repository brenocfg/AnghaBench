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
typedef  int /*<<< orphan*/  uint8_t ;
struct spdifContext {size_t out_buffer_len; int /*<<< orphan*/ * out_buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_ERR (struct spdifContext*,char*) ; 
 int OUTBUF_SIZE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int write_packet(void *p, uint8_t *buf, int buf_size)
{
    struct spdifContext *ctx = p;

    int buffer_left = OUTBUF_SIZE - ctx->out_buffer_len;
    if (buf_size > buffer_left) {
        MP_ERR(ctx, "spdif packet too large.\n");
        buf_size = buffer_left;
    }

    memcpy(&ctx->out_buffer[ctx->out_buffer_len], buf, buf_size);
    ctx->out_buffer_len += buf_size;
    return buf_size;
}