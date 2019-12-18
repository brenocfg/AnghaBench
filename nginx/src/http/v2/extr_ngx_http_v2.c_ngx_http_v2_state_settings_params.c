#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  int ssize_t ;
typedef  int ngx_uint_t ;
struct TYPE_18__ {int /*<<< orphan*/  concurrent_pushes; } ;
typedef  TYPE_4__ ngx_http_v2_srv_conf_t ;
typedef  int /*<<< orphan*/  ngx_http_v2_out_frame_t ;
struct TYPE_15__ {scalar_t__ length; } ;
struct TYPE_19__ {int init_window; int frame_size; int push_disabled; int table_update; int /*<<< orphan*/  concurrent_pushes; TYPE_3__* http_connection; TYPE_2__* connection; TYPE_1__ state; } ;
typedef  TYPE_5__ ngx_http_v2_connection_t ;
struct TYPE_17__ {int /*<<< orphan*/  conf_ctx; } ;
struct TYPE_16__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_HTTP_V2_ACK_FLAG ; 
 int NGX_HTTP_V2_DEFAULT_FRAME_SIZE ; 
#define  NGX_HTTP_V2_ENABLE_PUSH_SETTING 132 
 int /*<<< orphan*/  NGX_HTTP_V2_FLOW_CTRL_ERROR ; 
#define  NGX_HTTP_V2_HEADER_TABLE_SIZE_SETTING 131 
#define  NGX_HTTP_V2_INIT_WINDOW_SIZE_SETTING 130 
 int /*<<< orphan*/  NGX_HTTP_V2_INTERNAL_ERROR ; 
 int NGX_HTTP_V2_MAX_FRAME_SIZE ; 
#define  NGX_HTTP_V2_MAX_FRAME_SIZE_SETTING 129 
#define  NGX_HTTP_V2_MAX_STREAMS_SETTING 128 
 int NGX_HTTP_V2_MAX_WINDOW ; 
 int /*<<< orphan*/  NGX_HTTP_V2_PROTOCOL_ERROR ; 
 int /*<<< orphan*/  NGX_HTTP_V2_SETTINGS_ACK_SIZE ; 
 int /*<<< orphan*/  NGX_HTTP_V2_SETTINGS_FRAME ; 
 int NGX_HTTP_V2_SETTINGS_PARAM_SIZE ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_LOG_INFO ; 
 scalar_t__ NGX_OK ; 
 TYPE_4__* ngx_http_get_module_srv_conf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_http_v2_adjust_windows (TYPE_5__*,int) ; 
 int /*<<< orphan*/ * ngx_http_v2_connection_error (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ngx_http_v2_get_frame (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_v2_module ; 
 int ngx_http_v2_parse_uint16 (int /*<<< orphan*/ *) ; 
 int ngx_http_v2_parse_uint32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_v2_queue_ordered_frame (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ngx_http_v2_state_complete (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ngx_http_v2_state_save (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ * (*) (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *)) ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ngx_min (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u_char *
ngx_http_v2_state_settings_params(ngx_http_v2_connection_t *h2c, u_char *pos,
    u_char *end)
{
    ssize_t                   window_delta;
    ngx_uint_t                id, value;
    ngx_http_v2_srv_conf_t   *h2scf;
    ngx_http_v2_out_frame_t  *frame;

    window_delta = 0;

    while (h2c->state.length) {
        if (end - pos < NGX_HTTP_V2_SETTINGS_PARAM_SIZE) {
            return ngx_http_v2_state_save(h2c, pos, end,
                                          ngx_http_v2_state_settings_params);
        }

        h2c->state.length -= NGX_HTTP_V2_SETTINGS_PARAM_SIZE;

        id = ngx_http_v2_parse_uint16(pos);
        value = ngx_http_v2_parse_uint32(&pos[2]);

        ngx_log_debug2(NGX_LOG_DEBUG_HTTP, h2c->connection->log, 0,
                       "http2 setting %ui:%ui", id, value);

        switch (id) {

        case NGX_HTTP_V2_INIT_WINDOW_SIZE_SETTING:

            if (value > NGX_HTTP_V2_MAX_WINDOW) {
                ngx_log_error(NGX_LOG_INFO, h2c->connection->log, 0,
                              "client sent SETTINGS frame with incorrect "
                              "INITIAL_WINDOW_SIZE value %ui", value);

                return ngx_http_v2_connection_error(h2c,
                                                  NGX_HTTP_V2_FLOW_CTRL_ERROR);
            }

            window_delta = value - h2c->init_window;
            break;

        case NGX_HTTP_V2_MAX_FRAME_SIZE_SETTING:

            if (value > NGX_HTTP_V2_MAX_FRAME_SIZE
                || value < NGX_HTTP_V2_DEFAULT_FRAME_SIZE)
            {
                ngx_log_error(NGX_LOG_INFO, h2c->connection->log, 0,
                              "client sent SETTINGS frame with incorrect "
                              "MAX_FRAME_SIZE value %ui", value);

                return ngx_http_v2_connection_error(h2c,
                                                    NGX_HTTP_V2_PROTOCOL_ERROR);
            }

            h2c->frame_size = value;
            break;

        case NGX_HTTP_V2_ENABLE_PUSH_SETTING:

            if (value > 1) {
                ngx_log_error(NGX_LOG_INFO, h2c->connection->log, 0,
                              "client sent SETTINGS frame with incorrect "
                              "ENABLE_PUSH value %ui", value);

                return ngx_http_v2_connection_error(h2c,
                                                    NGX_HTTP_V2_PROTOCOL_ERROR);
            }

            h2c->push_disabled = !value;
            break;

        case NGX_HTTP_V2_MAX_STREAMS_SETTING:
            h2scf = ngx_http_get_module_srv_conf(h2c->http_connection->conf_ctx,
                                                 ngx_http_v2_module);

            h2c->concurrent_pushes = ngx_min(value, h2scf->concurrent_pushes);
            break;

        case NGX_HTTP_V2_HEADER_TABLE_SIZE_SETTING:

            h2c->table_update = 1;
            break;

        default:
            break;
        }

        pos += NGX_HTTP_V2_SETTINGS_PARAM_SIZE;
    }

    frame = ngx_http_v2_get_frame(h2c, NGX_HTTP_V2_SETTINGS_ACK_SIZE,
                                  NGX_HTTP_V2_SETTINGS_FRAME,
                                  NGX_HTTP_V2_ACK_FLAG, 0);
    if (frame == NULL) {
        return ngx_http_v2_connection_error(h2c, NGX_HTTP_V2_INTERNAL_ERROR);
    }

    ngx_http_v2_queue_ordered_frame(h2c, frame);

    if (window_delta) {
        h2c->init_window += window_delta;

        if (ngx_http_v2_adjust_windows(h2c, window_delta) != NGX_OK) {
            return ngx_http_v2_connection_error(h2c,
                                                NGX_HTTP_V2_INTERNAL_ERROR);
        }
    }

    return ngx_http_v2_state_complete(h2c, pos, end);
}