#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_11__ ;

/* Type definitions */
typedef  scalar_t__ time_t ;
struct TYPE_15__ {int count; scalar_t__ lingering_time; int lingering_close; TYPE_2__* connection; TYPE_1__* header_in; scalar_t__ keepalive; scalar_t__ reading_body; struct TYPE_15__* main; int /*<<< orphan*/  read_event_handler; scalar_t__ discard_body; scalar_t__ stream; } ;
typedef  TYPE_3__ ngx_http_request_t ;
struct TYPE_16__ {int lingering_time; scalar_t__ keepalive_timeout; scalar_t__ lingering_close; int /*<<< orphan*/  lingering_timeout; } ;
typedef  TYPE_4__ ngx_http_core_loc_conf_t ;
struct TYPE_14__ {TYPE_11__* read; } ;
struct TYPE_13__ {scalar_t__ pos; scalar_t__ last; } ;
struct TYPE_12__ {scalar_t__ ready; } ;

/* Variables and functions */
 scalar_t__ NGX_HTTP_LINGERING_ALWAYS ; 
 scalar_t__ NGX_HTTP_LINGERING_ON ; 
 int /*<<< orphan*/  ngx_add_timer (TYPE_11__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_exiting ; 
 int /*<<< orphan*/  ngx_http_close_request (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_core_module ; 
 int /*<<< orphan*/  ngx_http_discarded_request_body_handler ; 
 TYPE_4__* ngx_http_get_module_loc_conf (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_set_keepalive (TYPE_3__*) ; 
 int /*<<< orphan*/  ngx_http_set_lingering_close (TYPE_3__*) ; 
 int /*<<< orphan*/  ngx_terminate ; 
 scalar_t__ ngx_time () ; 

__attribute__((used)) static void
ngx_http_finalize_connection(ngx_http_request_t *r)
{
    ngx_http_core_loc_conf_t  *clcf;

#if (NGX_HTTP_V2)
    if (r->stream) {
        ngx_http_close_request(r, 0);
        return;
    }
#endif

    clcf = ngx_http_get_module_loc_conf(r, ngx_http_core_module);

    if (r->main->count != 1) {

        if (r->discard_body) {
            r->read_event_handler = ngx_http_discarded_request_body_handler;
            ngx_add_timer(r->connection->read, clcf->lingering_timeout);

            if (r->lingering_time == 0) {
                r->lingering_time = ngx_time()
                                      + (time_t) (clcf->lingering_time / 1000);
            }
        }

        ngx_http_close_request(r, 0);
        return;
    }

    r = r->main;

    if (r->reading_body) {
        r->keepalive = 0;
        r->lingering_close = 1;
    }

    if (!ngx_terminate
         && !ngx_exiting
         && r->keepalive
         && clcf->keepalive_timeout > 0)
    {
        ngx_http_set_keepalive(r);
        return;
    }

    if (clcf->lingering_close == NGX_HTTP_LINGERING_ALWAYS
        || (clcf->lingering_close == NGX_HTTP_LINGERING_ON
            && (r->lingering_close
                || r->header_in->pos < r->header_in->last
                || r->connection->read->ready)))
    {
        ngx_http_set_lingering_close(r);
        return;
    }

    ngx_http_close_request(r, 0);
}