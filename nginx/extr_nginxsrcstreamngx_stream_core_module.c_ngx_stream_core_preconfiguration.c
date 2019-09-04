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
typedef  int /*<<< orphan*/  ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_conf_t ;

/* Variables and functions */
 int /*<<< orphan*/  ngx_stream_variables_add_core_vars (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ngx_int_t
ngx_stream_core_preconfiguration(ngx_conf_t *cf)
{
    return ngx_stream_variables_add_core_vars(cf);
}