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
struct TYPE_3__ {size_t default_read_buf_len; } ;
typedef  TYPE_1__ SSL_CTX ;

/* Variables and functions */

void SSL_CTX_set_default_read_buffer_len(SSL_CTX *ctx, size_t len)
{
    ctx->default_read_buf_len = len;
}