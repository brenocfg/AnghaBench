#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_33__   TYPE_9__ ;
typedef  struct TYPE_32__   TYPE_8__ ;
typedef  struct TYPE_31__   TYPE_7__ ;
typedef  struct TYPE_30__   TYPE_4__ ;
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_1__ ;
typedef  struct TYPE_26__   TYPE_12__ ;
typedef  struct TYPE_25__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_29__ {TYPE_2__* connection; } ;
typedef  TYPE_3__ ngx_rtmp_session_t ;
struct TYPE_30__ {scalar_t__ type; } ;
typedef  TYPE_4__ ngx_rtmp_header_t ;
typedef  int (* ngx_rtmp_handler_pt ) (TYPE_3__*,TYPE_4__*,TYPE_7__*) ;
struct TYPE_32__ {int /*<<< orphan*/  amf_hash; } ;
typedef  TYPE_8__ ngx_rtmp_core_main_conf_t ;
struct TYPE_33__ {int member_3; int /*<<< orphan*/  type; int /*<<< orphan*/ * member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_9__ ngx_rtmp_amf_elt_t ;
struct TYPE_25__ {int /*<<< orphan*/  offset; TYPE_7__* link; int /*<<< orphan*/  log; } ;
typedef  TYPE_10__ ngx_rtmp_amf_ctx_t ;
typedef  int ngx_int_t ;
struct TYPE_31__ {TYPE_1__* buf; } ;
typedef  TYPE_7__ ngx_chain_t ;
struct TYPE_26__ {size_t nelts; int (* elts ) (TYPE_3__*,TYPE_4__*,TYPE_7__*) ;} ;
typedef  TYPE_12__ ngx_array_t ;
typedef  int /*<<< orphan*/  func ;
typedef  int /*<<< orphan*/  elts ;
typedef  int /*<<< orphan*/  act ;
struct TYPE_28__ {int /*<<< orphan*/  log; } ;
struct TYPE_27__ {scalar_t__* pos; scalar_t__* last; } ;

/* Variables and functions */
#define  NGX_DONE 131 
#define  NGX_ERROR 130 
 int /*<<< orphan*/  NGX_LOG_DEBUG_RTMP ; 
 scalar_t__ NGX_OK ; 
#define  NGX_RTMP_AMF_STRING 129 
 int /*<<< orphan*/  NGX_RTMP_AMF_TYPELESS ; 
 scalar_t__ NGX_RTMP_MSG_AMF3_CMD ; 
 scalar_t__ NGX_RTMP_MSG_AMF3_META ; 
 scalar_t__ NGX_RTMP_MSG_AMF3_SHARED ; 
 scalar_t__ NGX_RTMP_MSG_AMF_SHARED ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ * const,int /*<<< orphan*/ ,int) ; 
 TYPE_12__* ngx_hash_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ * const,size_t) ; 
 int /*<<< orphan*/  ngx_hash_strlow (int /*<<< orphan*/ * const,int /*<<< orphan*/ * const,size_t) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ngx_log_debug3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ * const,size_t,size_t) ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_10__*,int) ; 
#define  ngx_null_string 128 
 scalar_t__ ngx_rtmp_amf_read (TYPE_10__*,TYPE_9__*,int) ; 
 int /*<<< orphan*/  ngx_rtmp_core_module ; 
 TYPE_8__* ngx_rtmp_get_module_main_conf (TYPE_3__*,int /*<<< orphan*/ ) ; 
 size_t ngx_strlen (int /*<<< orphan*/ * const) ; 
 int stub1 (TYPE_3__*,TYPE_4__*,TYPE_7__*) ; 

ngx_int_t
ngx_rtmp_amf_message_handler(ngx_rtmp_session_t *s,
        ngx_rtmp_header_t *h, ngx_chain_t *in)
{
    ngx_rtmp_amf_ctx_t          act;
    ngx_rtmp_core_main_conf_t  *cmcf;
    ngx_array_t                *ch;
    ngx_rtmp_handler_pt        *ph;
    size_t                      len, n;

    static u_char               func[128];

    static ngx_rtmp_amf_elt_t   elts[] = {

        { NGX_RTMP_AMF_STRING,
          ngx_null_string,
          func,   sizeof(func) },
    };

    /* AMF command names come with string type, but shared object names
     * come without type */
    if (h->type == NGX_RTMP_MSG_AMF_SHARED ||
        h->type == NGX_RTMP_MSG_AMF3_SHARED)
    {
        elts[0].type |= NGX_RTMP_AMF_TYPELESS;
    } else {
        elts[0].type &= ~NGX_RTMP_AMF_TYPELESS;
    }

    if ((h->type == NGX_RTMP_MSG_AMF3_SHARED ||
         h->type == NGX_RTMP_MSG_AMF3_META ||
         h->type == NGX_RTMP_MSG_AMF3_CMD)
         && in->buf->last > in->buf->pos)
    {
        ngx_log_debug1(NGX_LOG_DEBUG_RTMP, s->connection->log, 0,
                "AMF3 prefix: %ui", (ngx_int_t)*in->buf->pos);
        ++in->buf->pos;
    }

    cmcf = ngx_rtmp_get_module_main_conf(s, ngx_rtmp_core_module);

    /* read AMF func name & transaction id */
    ngx_memzero(&act, sizeof(act));
    act.link = in;
    act.log = s->connection->log;
    memset(func, 0, sizeof(func));

    if (ngx_rtmp_amf_read(&act, elts,
                sizeof(elts) / sizeof(elts[0])) != NGX_OK)
    {
        ngx_log_debug0(NGX_LOG_DEBUG_RTMP, s->connection->log, 0,
                "AMF cmd failed");
        return NGX_ERROR;
    }

    /* skip name */
    in = act.link;
    in->buf->pos += act.offset;

    len = ngx_strlen(func);

    ch = ngx_hash_find(&cmcf->amf_hash,
            ngx_hash_strlow(func, func, len), func, len);

    if (ch && ch->nelts) {
        ph = ch->elts;
        for (n = 0; n < ch->nelts; ++n, ++ph) {
            ngx_log_debug3(NGX_LOG_DEBUG_RTMP, s->connection->log, 0,
                "AMF func '%s' passed to handler %d/%d",
                func, n, ch->nelts);
            switch ((*ph)(s, h, in)) {
                case NGX_ERROR:
                    return NGX_ERROR;
                case NGX_DONE:
                    return NGX_OK;
            }
        }
    } else {
        ngx_log_debug1(NGX_LOG_DEBUG_RTMP, s->connection->log, 0,
            "AMF cmd '%s' no handler", func);
    }

    return NGX_OK;
}