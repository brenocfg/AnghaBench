#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
typedef  char u_char ;
typedef  int /*<<< orphan*/  ngx_int_t ;
typedef  int ngx_http_ssi_state_e ;
struct TYPE_18__ {int len; char* data; } ;
struct TYPE_13__ {int /*<<< orphan*/  nelts; } ;
struct TYPE_19__ {int state; size_t looked; char* copy_end; char* pos; char* value_buf; int value_len; int saved_state; TYPE_4__* buf; int /*<<< orphan*/ * copy_start; TYPE_5__ command; TYPE_10__* param; TYPE_11__ params; void* key; int /*<<< orphan*/  saved; } ;
typedef  TYPE_6__ ngx_http_ssi_ctx_t ;
struct TYPE_20__ {TYPE_3__* connection; int /*<<< orphan*/  pool; } ;
typedef  TYPE_7__ ngx_http_request_t ;
struct TYPE_17__ {char* last; int /*<<< orphan*/ * pos; } ;
struct TYPE_16__ {int /*<<< orphan*/  log; } ;
struct TYPE_15__ {int len; char* data; } ;
struct TYPE_14__ {int len; char* data; } ;
struct TYPE_12__ {TYPE_2__ key; TYPE_1__ value; } ;

/* Variables and functions */
#define  CR 149 
#define  LF 148 
 int /*<<< orphan*/  NGX_AGAIN ; 
 int /*<<< orphan*/  NGX_ERROR ; 
 int NGX_HTTP_SSI_COMMAND_LEN ; 
 int /*<<< orphan*/  NGX_HTTP_SSI_ERROR ; 
 int NGX_HTTP_SSI_PARAM_LEN ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 int /*<<< orphan*/  NGX_OK ; 
 TYPE_10__* ngx_array_push (TYPE_11__*) ; 
 void* ngx_hash (void*,char) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ngx_memcpy (char*,char*,int) ; 
 void* ngx_pnalloc (int /*<<< orphan*/ ,int) ; 
#define  ssi_command_state 147 
#define  ssi_comment0_state 146 
#define  ssi_comment1_state 145 
#define  ssi_comment_end0_state 144 
#define  ssi_comment_end1_state 143 
#define  ssi_double_quoted_value_state 142 
#define  ssi_error_end0_state 141 
#define  ssi_error_end1_state 140 
#define  ssi_error_state 139 
#define  ssi_param_state 138 
#define  ssi_postparam_state 137 
#define  ssi_precommand_state 136 
#define  ssi_preequal_state 135 
#define  ssi_preparam_state 134 
#define  ssi_prevalue_state 133 
#define  ssi_quoted_symbol_state 132 
#define  ssi_quoted_value_state 131 
#define  ssi_sharp_state 130 
#define  ssi_start_state 129 
#define  ssi_tag_state 128 

__attribute__((used)) static ngx_int_t
ngx_http_ssi_parse(ngx_http_request_t *r, ngx_http_ssi_ctx_t *ctx)
{
    u_char                *p, *value, *last, *copy_end, ch;
    size_t                 looked;
    ngx_http_ssi_state_e   state;

    state = ctx->state;
    looked = ctx->looked;
    last = ctx->buf->last;
    copy_end = ctx->copy_end;

    for (p = ctx->pos; p < last; p++) {

        ch = *p;

        if (state == ssi_start_state) {

            /* the tight loop */

            for ( ;; ) {
                if (ch == '<') {
                    copy_end = p;
                    looked = 1;
                    state = ssi_tag_state;

                    goto tag_started;
                }

                if (++p == last) {
                    break;
                }

                ch = *p;
            }

            ctx->state = state;
            ctx->pos = p;
            ctx->looked = looked;
            ctx->copy_end = p;

            if (ctx->copy_start == NULL) {
                ctx->copy_start = ctx->buf->pos;
            }

            return NGX_AGAIN;

        tag_started:

            continue;
        }

        switch (state) {

        case ssi_start_state:
            /* not reached */
            break;

        case ssi_tag_state:
            switch (ch) {
            case '!':
                looked = 2;
                state = ssi_comment0_state;
                break;

            case '<':
                copy_end = p;
                break;

            default:
                copy_end = p;
                looked = 0;
                state = ssi_start_state;
                break;
            }

            break;

        case ssi_comment0_state:
            switch (ch) {
            case '-':
                looked = 3;
                state = ssi_comment1_state;
                break;

            case '<':
                copy_end = p;
                looked = 1;
                state = ssi_tag_state;
                break;

            default:
                copy_end = p;
                looked = 0;
                state = ssi_start_state;
                break;
            }

            break;

        case ssi_comment1_state:
            switch (ch) {
            case '-':
                looked = 4;
                state = ssi_sharp_state;
                break;

            case '<':
                copy_end = p;
                looked = 1;
                state = ssi_tag_state;
                break;

            default:
                copy_end = p;
                looked = 0;
                state = ssi_start_state;
                break;
            }

            break;

        case ssi_sharp_state:
            switch (ch) {
            case '#':
                if (p - ctx->pos < 4) {
                    ctx->saved = 0;
                }
                looked = 0;
                state = ssi_precommand_state;
                break;

            case '<':
                copy_end = p;
                looked = 1;
                state = ssi_tag_state;
                break;

            default:
                copy_end = p;
                looked = 0;
                state = ssi_start_state;
                break;
            }

            break;

        case ssi_precommand_state:
            switch (ch) {
            case ' ':
            case CR:
            case LF:
            case '\t':
                break;

            default:
                ctx->command.len = 1;
                ctx->command.data = ngx_pnalloc(r->pool,
                                                NGX_HTTP_SSI_COMMAND_LEN);
                if (ctx->command.data == NULL) {
                    return NGX_ERROR;
                }

                ctx->command.data[0] = ch;

                ctx->key = 0;
                ctx->key = ngx_hash(ctx->key, ch);

                ctx->params.nelts = 0;

                state = ssi_command_state;
                break;
            }

            break;

        case ssi_command_state:
            switch (ch) {
            case ' ':
            case CR:
            case LF:
            case '\t':
                state = ssi_preparam_state;
                break;

            case '-':
                state = ssi_comment_end0_state;
                break;

            default:
                if (ctx->command.len == NGX_HTTP_SSI_COMMAND_LEN) {
                    ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                                  "the \"%V%c...\" SSI command is too long",
                                  &ctx->command, ch);

                    state = ssi_error_state;
                    break;
                }

                ctx->command.data[ctx->command.len++] = ch;
                ctx->key = ngx_hash(ctx->key, ch);
            }

            break;

        case ssi_preparam_state:
            switch (ch) {
            case ' ':
            case CR:
            case LF:
            case '\t':
                break;

            case '-':
                state = ssi_comment_end0_state;
                break;

            default:
                ctx->param = ngx_array_push(&ctx->params);
                if (ctx->param == NULL) {
                    return NGX_ERROR;
                }

                ctx->param->key.len = 1;
                ctx->param->key.data = ngx_pnalloc(r->pool,
                                                   NGX_HTTP_SSI_PARAM_LEN);
                if (ctx->param->key.data == NULL) {
                    return NGX_ERROR;
                }

                ctx->param->key.data[0] = ch;

                ctx->param->value.len = 0;

                if (ctx->value_buf == NULL) {
                    ctx->param->value.data = ngx_pnalloc(r->pool,
                                                         ctx->value_len + 1);
                    if (ctx->param->value.data == NULL) {
                        return NGX_ERROR;
                    }

                } else {
                    ctx->param->value.data = ctx->value_buf;
                }

                state = ssi_param_state;
                break;
            }

            break;

        case ssi_param_state:
            switch (ch) {
            case ' ':
            case CR:
            case LF:
            case '\t':
                state = ssi_preequal_state;
                break;

            case '=':
                state = ssi_prevalue_state;
                break;

            case '-':
                state = ssi_error_end0_state;

                ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                              "unexpected \"-\" symbol after \"%V\" "
                              "parameter in \"%V\" SSI command",
                              &ctx->param->key, &ctx->command);
                break;

            default:
                if (ctx->param->key.len == NGX_HTTP_SSI_PARAM_LEN) {
                    state = ssi_error_state;
                    ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                                  "too long \"%V%c...\" parameter in "
                                  "\"%V\" SSI command",
                                  &ctx->param->key, ch, &ctx->command);
                    break;
                }

                ctx->param->key.data[ctx->param->key.len++] = ch;
            }

            break;

        case ssi_preequal_state:
            switch (ch) {
            case ' ':
            case CR:
            case LF:
            case '\t':
                break;

            case '=':
                state = ssi_prevalue_state;
                break;

            default:
                if (ch == '-') {
                    state = ssi_error_end0_state;
                } else {
                    state = ssi_error_state;
                }

                ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                              "unexpected \"%c\" symbol after \"%V\" "
                              "parameter in \"%V\" SSI command",
                              ch, &ctx->param->key, &ctx->command);
                break;
            }

            break;

        case ssi_prevalue_state:
            switch (ch) {
            case ' ':
            case CR:
            case LF:
            case '\t':
                break;

            case '"':
                state = ssi_double_quoted_value_state;
                break;

            case '\'':
                state = ssi_quoted_value_state;
                break;

            default:
                if (ch == '-') {
                    state = ssi_error_end0_state;
                } else {
                    state = ssi_error_state;
                }

                ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                              "unexpected \"%c\" symbol before value of "
                              "\"%V\" parameter in \"%V\" SSI command",
                              ch, &ctx->param->key, &ctx->command);
                break;
            }

            break;

        case ssi_double_quoted_value_state:
            switch (ch) {
            case '"':
                state = ssi_postparam_state;
                break;

            case '\\':
                ctx->saved_state = ssi_double_quoted_value_state;
                state = ssi_quoted_symbol_state;

                /* fall through */

            default:
                if (ctx->param->value.len == ctx->value_len) {
                    ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                                  "too long \"%V%c...\" value of \"%V\" "
                                  "parameter in \"%V\" SSI command",
                                  &ctx->param->value, ch, &ctx->param->key,
                                  &ctx->command);
                    state = ssi_error_state;
                    break;
                }

                ctx->param->value.data[ctx->param->value.len++] = ch;
            }

            break;

        case ssi_quoted_value_state:
            switch (ch) {
            case '\'':
                state = ssi_postparam_state;
                break;

            case '\\':
                ctx->saved_state = ssi_quoted_value_state;
                state = ssi_quoted_symbol_state;

                /* fall through */

            default:
                if (ctx->param->value.len == ctx->value_len) {
                    ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                                  "too long \"%V%c...\" value of \"%V\" "
                                  "parameter in \"%V\" SSI command",
                                  &ctx->param->value, ch, &ctx->param->key,
                                  &ctx->command);
                    state = ssi_error_state;
                    break;
                }

                ctx->param->value.data[ctx->param->value.len++] = ch;
            }

            break;

        case ssi_quoted_symbol_state:
            state = ctx->saved_state;

            if (ctx->param->value.len == ctx->value_len) {
                ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                              "too long \"%V%c...\" value of \"%V\" "
                              "parameter in \"%V\" SSI command",
                              &ctx->param->value, ch, &ctx->param->key,
                              &ctx->command);
                state = ssi_error_state;
                break;
            }

            ctx->param->value.data[ctx->param->value.len++] = ch;

            break;

        case ssi_postparam_state:

            if (ctx->param->value.len + 1 < ctx->value_len / 2) {
                value = ngx_pnalloc(r->pool, ctx->param->value.len + 1);
                if (value == NULL) {
                    return NGX_ERROR;
                }

                ngx_memcpy(value, ctx->param->value.data,
                           ctx->param->value.len);

                ctx->value_buf = ctx->param->value.data;
                ctx->param->value.data = value;

            } else {
                ctx->value_buf = NULL;
            }

            switch (ch) {
            case ' ':
            case CR:
            case LF:
            case '\t':
                state = ssi_preparam_state;
                break;

            case '-':
                state = ssi_comment_end0_state;
                break;

            default:
                ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                              "unexpected \"%c\" symbol after \"%V\" value "
                              "of \"%V\" parameter in \"%V\" SSI command",
                              ch, &ctx->param->value, &ctx->param->key,
                              &ctx->command);
                state = ssi_error_state;
                break;
            }

            break;

        case ssi_comment_end0_state:
            switch (ch) {
            case '-':
                state = ssi_comment_end1_state;
                break;

            default:
                ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                              "unexpected \"%c\" symbol in \"%V\" SSI command",
                              ch, &ctx->command);
                state = ssi_error_state;
                break;
            }

            break;

        case ssi_comment_end1_state:
            switch (ch) {
            case '>':
                ctx->state = ssi_start_state;
                ctx->pos = p + 1;
                ctx->looked = looked;
                ctx->copy_end = copy_end;

                if (ctx->copy_start == NULL && copy_end) {
                    ctx->copy_start = ctx->buf->pos;
                }

                return NGX_OK;

            default:
                ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                              "unexpected \"%c\" symbol in \"%V\" SSI command",
                              ch, &ctx->command);
                state = ssi_error_state;
                break;
            }

            break;

        case ssi_error_state:
            switch (ch) {
            case '-':
                state = ssi_error_end0_state;
                break;

            default:
                break;
            }

            break;

        case ssi_error_end0_state:
            switch (ch) {
            case '-':
                state = ssi_error_end1_state;
                break;

            default:
                state = ssi_error_state;
                break;
            }

            break;

        case ssi_error_end1_state:
            switch (ch) {
            case '>':
                ctx->state = ssi_start_state;
                ctx->pos = p + 1;
                ctx->looked = looked;
                ctx->copy_end = copy_end;

                if (ctx->copy_start == NULL && copy_end) {
                    ctx->copy_start = ctx->buf->pos;
                }

                return NGX_HTTP_SSI_ERROR;

            default:
                state = ssi_error_state;
                break;
            }

            break;
        }
    }

    ctx->state = state;
    ctx->pos = p;
    ctx->looked = looked;

    ctx->copy_end = (state == ssi_start_state) ? p : copy_end;

    if (ctx->copy_start == NULL && ctx->copy_end) {
        ctx->copy_start = ctx->buf->pos;
    }

    return NGX_AGAIN;
}