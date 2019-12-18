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
struct cs_base64_ctx {void* user_data; int /*<<< orphan*/  b64_putc; scalar_t__ chunk_size; } ;
typedef  int /*<<< orphan*/  cs_base64_putc_t ;

/* Variables and functions */

void cs_base64_init(struct cs_base64_ctx *ctx, cs_base64_putc_t b64_putc,
                    void *user_data) {
  ctx->chunk_size = 0;
  ctx->b64_putc = b64_putc;
  ctx->user_data = user_data;
}