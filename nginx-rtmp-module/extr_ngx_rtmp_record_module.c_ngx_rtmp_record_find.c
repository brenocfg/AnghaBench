#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ngx_uint_t ;
struct TYPE_9__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
typedef  TYPE_3__ ngx_str_t ;
struct TYPE_7__ {int /*<<< orphan*/  data; int /*<<< orphan*/  len; } ;
struct TYPE_8__ {scalar_t__ nelts; TYPE_4__** elts; } ;
struct TYPE_10__ {TYPE_1__ id; TYPE_2__ rec; } ;
typedef  TYPE_4__ ngx_rtmp_record_app_conf_t ;

/* Variables and functions */
 scalar_t__ NGX_CONF_UNSET_UINT ; 
 scalar_t__ ngx_strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

ngx_uint_t
ngx_rtmp_record_find(ngx_rtmp_record_app_conf_t *racf, ngx_str_t *id)
{
    ngx_rtmp_record_app_conf_t    **pracf, *rracf;
    ngx_uint_t                      n;

    pracf = racf->rec.elts;

    for (n = 0; n < racf->rec.nelts; ++n, ++pracf) {
        rracf = *pracf;

        if (rracf->id.len == id->len &&
            ngx_strncmp(rracf->id.data, id->data, id->len) == 0)
        {
            return n;
        }
    }

    return NGX_CONF_UNSET_UINT;
}