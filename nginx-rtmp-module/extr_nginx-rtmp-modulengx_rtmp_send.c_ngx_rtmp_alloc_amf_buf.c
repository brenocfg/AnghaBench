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
typedef  int /*<<< orphan*/  ngx_rtmp_core_srv_conf_t ;
typedef  int /*<<< orphan*/  ngx_chain_t ;

/* Variables and functions */
 int /*<<< orphan*/ * ngx_rtmp_alloc_shared_buf (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ngx_chain_t *
ngx_rtmp_alloc_amf_buf(void *arg)
{
    return ngx_rtmp_alloc_shared_buf((ngx_rtmp_core_srv_conf_t *)arg);
}