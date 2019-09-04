#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_rtmp_exec_conf_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_5__ {scalar_t__ nelts; int /*<<< orphan*/ * elts; } ;
typedef  TYPE_1__ ngx_array_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/ * ngx_array_push_n (TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_exec_merge_confs(ngx_array_t *conf, ngx_array_t *prev)
{
    size_t                 n;
    ngx_rtmp_exec_conf_t  *ec, *pec;

    if (prev->nelts == 0) {
        return NGX_OK;
    }

    if (conf->nelts == 0) {
        *conf = *prev;
        return NGX_OK;
    }

    ec = ngx_array_push_n(conf, prev->nelts);
    if (ec == NULL) {
        return NGX_ERROR;
    }

    pec = prev->elts;
    for (n = 0; n < prev->nelts; n++, ec++, pec++) {
        *ec = *pec;
    }

    return NGX_OK;
}