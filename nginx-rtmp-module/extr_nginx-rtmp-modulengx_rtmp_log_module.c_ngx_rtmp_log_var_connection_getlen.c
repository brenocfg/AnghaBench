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
typedef  int /*<<< orphan*/  ngx_rtmp_session_t ;
typedef  int /*<<< orphan*/  ngx_rtmp_log_op_t ;

/* Variables and functions */
 size_t NGX_INT_T_LEN ; 

__attribute__((used)) static size_t
ngx_rtmp_log_var_connection_getlen(ngx_rtmp_session_t *s, ngx_rtmp_log_op_t *op)
{
    return NGX_INT_T_LEN;
}