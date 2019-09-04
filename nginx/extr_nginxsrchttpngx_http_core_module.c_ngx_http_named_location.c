#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_8__ ;
typedef  struct TYPE_30__   TYPE_7__ ;
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;
typedef  struct TYPE_23__   TYPE_12__ ;
typedef  struct TYPE_22__   TYPE_11__ ;

/* Type definitions */
struct TYPE_27__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
typedef  TYPE_4__ ngx_str_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_22__ {scalar_t__ len; } ;
struct TYPE_28__ {scalar_t__ uri_changes; int internal; TYPE_3__* connection; int /*<<< orphan*/  (* write_event_handler ) (TYPE_5__*) ;int /*<<< orphan*/  phase_handler; int /*<<< orphan*/  ctx; int /*<<< orphan*/  loc_conf; scalar_t__ uri_changed; int /*<<< orphan*/ * content_handler; int /*<<< orphan*/  args; TYPE_11__ uri; TYPE_1__* main; } ;
typedef  TYPE_5__ ngx_http_request_t ;
struct TYPE_29__ {TYPE_8__** named_locations; } ;
typedef  TYPE_6__ ngx_http_core_srv_conf_t ;
struct TYPE_25__ {int /*<<< orphan*/  location_rewrite_index; } ;
struct TYPE_30__ {TYPE_2__ phase_engine; } ;
typedef  TYPE_7__ ngx_http_core_main_conf_t ;
struct TYPE_23__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct TYPE_31__ {int /*<<< orphan*/  loc_conf; TYPE_12__ name; } ;
typedef  TYPE_8__ ngx_http_core_loc_conf_t ;
struct TYPE_26__ {int /*<<< orphan*/  log; } ;
struct TYPE_24__ {int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_DONE ; 
 int /*<<< orphan*/  NGX_HTTP_INTERNAL_SERVER_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 int /*<<< orphan*/  ngx_http_core_module ; 
 int /*<<< orphan*/  ngx_http_core_run_phases (TYPE_5__*) ; 
 int /*<<< orphan*/  ngx_http_finalize_request (TYPE_5__*,int /*<<< orphan*/ ) ; 
 TYPE_7__* ngx_http_get_module_main_conf (TYPE_5__*,int /*<<< orphan*/ ) ; 
 TYPE_6__* ngx_http_get_module_srv_conf (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int ngx_http_max_module ; 
 int /*<<< orphan*/  ngx_http_update_location_config (TYPE_5__*) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_12__*) ; 
 int /*<<< orphan*/  ngx_log_debug3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_4__*,TYPE_11__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_4__*) ; 
 int /*<<< orphan*/  ngx_memzero (int /*<<< orphan*/ ,int) ; 
 scalar_t__ ngx_strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

ngx_int_t
ngx_http_named_location(ngx_http_request_t *r, ngx_str_t *name)
{
    ngx_http_core_srv_conf_t    *cscf;
    ngx_http_core_loc_conf_t   **clcfp;
    ngx_http_core_main_conf_t   *cmcf;

    r->main->count++;
    r->uri_changes--;

    if (r->uri_changes == 0) {
        ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                      "rewrite or internal redirection cycle "
                      "while redirect to named location \"%V\"", name);

        ngx_http_finalize_request(r, NGX_HTTP_INTERNAL_SERVER_ERROR);
        return NGX_DONE;
    }

    if (r->uri.len == 0) {
        ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                      "empty URI in redirect to named location \"%V\"", name);

        ngx_http_finalize_request(r, NGX_HTTP_INTERNAL_SERVER_ERROR);
        return NGX_DONE;
    }

    cscf = ngx_http_get_module_srv_conf(r, ngx_http_core_module);

    if (cscf->named_locations) {

        for (clcfp = cscf->named_locations; *clcfp; clcfp++) {

            ngx_log_debug1(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                           "test location: \"%V\"", &(*clcfp)->name);

            if (name->len != (*clcfp)->name.len
                || ngx_strncmp(name->data, (*clcfp)->name.data, name->len) != 0)
            {
                continue;
            }

            ngx_log_debug3(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                           "using location: %V \"%V?%V\"",
                           name, &r->uri, &r->args);

            r->internal = 1;
            r->content_handler = NULL;
            r->uri_changed = 0;
            r->loc_conf = (*clcfp)->loc_conf;

            /* clear the modules contexts */
            ngx_memzero(r->ctx, sizeof(void *) * ngx_http_max_module);

            ngx_http_update_location_config(r);

            cmcf = ngx_http_get_module_main_conf(r, ngx_http_core_module);

            r->phase_handler = cmcf->phase_engine.location_rewrite_index;

            r->write_event_handler = ngx_http_core_run_phases;
            ngx_http_core_run_phases(r);

            return NGX_DONE;
        }
    }

    ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                  "could not find named location \"%V\"", name);

    ngx_http_finalize_request(r, NGX_HTTP_INTERNAL_SERVER_ERROR);

    return NGX_DONE;
}