#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
struct TYPE_5__ {int len; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ ngx_str_t ;
typedef  scalar_t__ ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_http_request_t ;
typedef  int /*<<< orphan*/  ngx_http_complex_value_t ;
struct TYPE_6__ {size_t nelts; int /*<<< orphan*/ * elts; } ;
typedef  TYPE_2__ ngx_array_t ;

/* Variables and functions */
 scalar_t__ NGX_DECLINED ; 
 scalar_t__ NGX_ERROR ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_http_complex_value (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 

ngx_int_t
ngx_http_test_predicates(ngx_http_request_t *r, ngx_array_t *predicates)
{
    ngx_str_t                  val;
    ngx_uint_t                 i;
    ngx_http_complex_value_t  *cv;

    if (predicates == NULL) {
        return NGX_OK;
    }

    cv = predicates->elts;

    for (i = 0; i < predicates->nelts; i++) {
        if (ngx_http_complex_value(r, &cv[i], &val) != NGX_OK) {
            return NGX_ERROR;
        }

        if (val.len && (val.len != 1 || val.data[0] != '0')) {
            return NGX_DECLINED;
        }
    }

    return NGX_OK;
}