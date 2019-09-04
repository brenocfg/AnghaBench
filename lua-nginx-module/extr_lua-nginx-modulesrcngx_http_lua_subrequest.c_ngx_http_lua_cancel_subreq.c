#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  parent; TYPE_1__* connection; TYPE_2__* main; } ;
typedef  TYPE_3__ ngx_http_request_t ;
struct TYPE_9__ {struct TYPE_9__* next; } ;
typedef  TYPE_4__ ngx_http_posted_request_t ;
struct TYPE_7__ {TYPE_4__* posted_requests; int /*<<< orphan*/  subrequests; int /*<<< orphan*/  count; } ;
struct TYPE_6__ {int /*<<< orphan*/  data; } ;

/* Variables and functions */

__attribute__((used)) static void
ngx_http_lua_cancel_subreq(ngx_http_request_t *r)
{
    ngx_http_posted_request_t   *pr;
    ngx_http_posted_request_t  **p;

#if 1
    r->main->count--;
    r->main->subrequests++;
#endif

    p = &r->main->posted_requests;
    for (pr = r->main->posted_requests; pr->next; pr = pr->next) {
        p = &pr->next;
    }

    *p = NULL;

    r->connection->data = r->parent;
}