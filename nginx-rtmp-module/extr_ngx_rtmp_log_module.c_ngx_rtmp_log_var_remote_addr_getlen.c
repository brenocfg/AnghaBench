#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* connection; } ;
typedef  TYPE_3__ ngx_rtmp_session_t ;
typedef  int /*<<< orphan*/  ngx_rtmp_log_op_t ;
struct TYPE_5__ {size_t len; } ;
struct TYPE_6__ {TYPE_1__ addr_text; } ;

/* Variables and functions */

__attribute__((used)) static size_t
ngx_rtmp_log_var_remote_addr_getlen(ngx_rtmp_session_t *s,
    ngx_rtmp_log_op_t *op)
{
    return s->connection->addr_text.len;
}