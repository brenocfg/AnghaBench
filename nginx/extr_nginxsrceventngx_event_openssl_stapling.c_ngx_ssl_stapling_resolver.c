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
typedef  int /*<<< orphan*/  ngx_ssl_t ;
typedef  int /*<<< orphan*/  ngx_resolver_t ;
typedef  int /*<<< orphan*/  ngx_msec_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_conf_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_OK ; 

ngx_int_t
ngx_ssl_stapling_resolver(ngx_conf_t *cf, ngx_ssl_t *ssl,
    ngx_resolver_t *resolver, ngx_msec_t resolver_timeout)
{
    return NGX_OK;
}