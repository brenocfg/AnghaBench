#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  char u_char ;
typedef  size_t ngx_uint_t ;
struct TYPE_18__ {size_t len; char* data; } ;
typedef  TYPE_3__ ngx_str_t ;
typedef  int ngx_int_t ;
struct TYPE_19__ {size_t start_line; scalar_t__ token_len; } ;
typedef  TYPE_4__ ngx_http_lua_block_parser_ctx_t ;
struct TYPE_20__ {char* (* handler ) (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/  handler_conf; TYPE_6__* args; int /*<<< orphan*/  pool; TYPE_2__* conf_file; int /*<<< orphan*/  temp_pool; } ;
typedef  TYPE_5__ ngx_conf_t ;
typedef  int /*<<< orphan*/  ngx_command_t ;
struct TYPE_21__ {size_t nelts; TYPE_3__* elts; } ;
typedef  TYPE_6__ ngx_array_t ;
struct TYPE_16__ {scalar_t__ fd; } ;
struct TYPE_17__ {size_t line; TYPE_1__ file; } ;

/* Variables and functions */
#define  FOUND_COMMENT_LINE 136 
#define  FOUND_DOUBLE_QUOTED 135 
#define  FOUND_LBRACKET_CMT 134 
#define  FOUND_LBRACKET_STR 133 
#define  FOUND_LEFT_CURLY 132 
#define  FOUND_RIGHT_CURLY 131 
#define  FOUND_RIGHT_LBRACKET 130 
#define  FOUND_SINGLE_QUOTED 129 
 char* NGX_CONF_ERROR ; 
 char* NGX_CONF_OK ; 
#define  NGX_ERROR 128 
 scalar_t__ NGX_INVALID_FILE ; 
 int /*<<< orphan*/  NGX_LOG_EMERG ; 
 int /*<<< orphan*/  dd (char*,int) ; 
 TYPE_6__* ngx_array_create (int /*<<< orphan*/ ,int,int) ; 
 TYPE_3__* ngx_array_push (TYPE_6__*) ; 
 int /*<<< orphan*/  ngx_conf_log_error (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ,char*,...) ; 
 char* ngx_copy (char*,char*,size_t) ; 
 int /*<<< orphan*/  ngx_http_lua_assert (char* (*) (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ )) ; 
 int ngx_http_lua_conf_read_lua_token (TYPE_5__*,TYPE_4__*) ; 
 char* ngx_palloc (int /*<<< orphan*/ ,size_t) ; 
 char* stub1 (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

char *
ngx_http_lua_conf_lua_block_parse(ngx_conf_t *cf, ngx_command_t *cmd)
{
    ngx_http_lua_block_parser_ctx_t     ctx;

    int               level = 1;
    char             *rv;
    u_char           *p;
    size_t            len;
    ngx_str_t        *src, *dst;
    ngx_int_t         rc;
    ngx_uint_t        i, start_line;
    ngx_array_t      *saved;
    enum {
        parse_block = 0,
        parse_param
    } type;

    if (cf->conf_file->file.fd != NGX_INVALID_FILE) {

        type = parse_block;

    } else {
        type = parse_param;
    }

    saved = cf->args;

    cf->args = ngx_array_create(cf->temp_pool, 4, sizeof(ngx_str_t));
    if (cf->args == NULL) {
        return NGX_CONF_ERROR;
    }

    ctx.token_len = 0;
    start_line = cf->conf_file->line;

    dd("init start line: %d", (int) start_line);

    ctx.start_line = start_line;

    for ( ;; ) {
        rc = ngx_http_lua_conf_read_lua_token(cf, &ctx);

        dd("parser start line: %d", (int) start_line);

        switch (rc) {

        case NGX_ERROR:
            goto done;

        case FOUND_LEFT_CURLY:

            ctx.start_line = cf->conf_file->line;

            if (type == parse_param) {
                ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                                   "block directives are not supported "
                                   "in -g option");
                goto failed;
            }

            level++;
            dd("seen block start: level=%d", (int) level);
            break;

        case FOUND_RIGHT_CURLY:

            level--;
            dd("seen block done: level=%d", (int) level);

            if (type != parse_block || level < 0) {
                ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                                   "unexpected \"}\": level %d, "
                                   "starting at line %ui", level,
                                   start_line);
                goto failed;
            }

            if (level == 0) {
                ngx_http_lua_assert(cf->handler);

                src = cf->args->elts;

                for (len = 0, i = 0; i < cf->args->nelts; i++) {
                    len += src[i].len;
                }

                dd("saved nelts: %d", (int) saved->nelts);
                dd("temp nelts: %d", (int) cf->args->nelts);
#if 0
                ngx_http_lua_assert(saved->nelts == 1);
#endif

                dst = ngx_array_push(saved);
                if (dst == NULL) {
                    return NGX_CONF_ERROR;
                }
                dst->len = len;
                dst->len--;  /* skip the trailing '}' block terminator */

                p = ngx_palloc(cf->pool, len);
                if (p == NULL) {
                    return NGX_CONF_ERROR;
                }
                dst->data = p;

                for (i = 0; i < cf->args->nelts; i++) {
                    p = ngx_copy(p, src[i].data, src[i].len);
                }

                p[-1] = '\0';  /* override the last '}' char to null */

                cf->args = saved;

                rv = (*cf->handler)(cf, cmd, cf->handler_conf);
                if (rv == NGX_CONF_OK) {
                    goto done;
                }

                if (rv == NGX_CONF_ERROR) {
                    goto failed;
                }

                ngx_conf_log_error(NGX_LOG_EMERG, cf, 0, rv);

                goto failed;
            }

            break;

        case FOUND_LBRACKET_STR:
        case FOUND_LBRACKET_CMT:
        case FOUND_RIGHT_LBRACKET:
        case FOUND_COMMENT_LINE:
        case FOUND_DOUBLE_QUOTED:
        case FOUND_SINGLE_QUOTED:
            break;

        default:

            ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                               "unknown return value from the lexer: %i", rc);
            goto failed;
        }
    }

failed:

    rc = NGX_ERROR;

done:

    if (rc == NGX_ERROR) {
        return NGX_CONF_ERROR;
    }

    return NGX_CONF_OK;
}