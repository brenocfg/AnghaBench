#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_9__ ;
typedef  struct TYPE_31__   TYPE_8__ ;
typedef  struct TYPE_30__   TYPE_7__ ;
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;
typedef  struct TYPE_23__   TYPE_19__ ;
typedef  struct TYPE_22__   TYPE_18__ ;
typedef  struct TYPE_21__   TYPE_11__ ;
typedef  struct TYPE_20__   TYPE_10__ ;

/* Type definitions */
struct TYPE_28__ {scalar_t__ len; } ;
struct TYPE_30__ {int protocol; int /*<<< orphan*/  mail_state; TYPE_5__ out; TYPE_8__* proxy; TYPE_4__* connection; } ;
typedef  TYPE_7__ ngx_mail_session_t ;
struct TYPE_22__ {TYPE_6__* connection; int /*<<< orphan*/  log_error; TYPE_1__* log; int /*<<< orphan*/  get; int /*<<< orphan*/ * name; int /*<<< orphan*/  socklen; int /*<<< orphan*/  sockaddr; } ;
struct TYPE_31__ {TYPE_18__ upstream; int /*<<< orphan*/ * buffer; } ;
typedef  TYPE_8__ ngx_mail_proxy_ctx_t ;
struct TYPE_32__ {int /*<<< orphan*/  buffer_size; } ;
typedef  TYPE_9__ ngx_mail_proxy_conf_t ;
struct TYPE_20__ {int /*<<< orphan*/  timeout; } ;
typedef  TYPE_10__ ngx_mail_core_srv_conf_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_21__ {int /*<<< orphan*/  name; int /*<<< orphan*/  socklen; int /*<<< orphan*/  sockaddr; } ;
typedef  TYPE_11__ ngx_addr_t ;
struct TYPE_29__ {TYPE_19__* read; TYPE_3__* write; int /*<<< orphan*/  pool; TYPE_7__* data; } ;
struct TYPE_27__ {int /*<<< orphan*/  pool; TYPE_2__* read; TYPE_1__* log; } ;
struct TYPE_26__ {int /*<<< orphan*/  handler; } ;
struct TYPE_25__ {int /*<<< orphan*/  handler; } ;
struct TYPE_24__ {char* action; } ;
struct TYPE_23__ {int /*<<< orphan*/  handler; } ;

/* Variables and functions */
 scalar_t__ NGX_BUSY ; 
 scalar_t__ NGX_DECLINED ; 
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_ERROR_ERR ; 
#define  NGX_MAIL_IMAP_PROTOCOL 129 
#define  NGX_MAIL_POP3_PROTOCOL 128 
 int /*<<< orphan*/  ngx_add_timer (TYPE_19__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ngx_create_temp_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_event_connect_peer (TYPE_18__*) ; 
 int /*<<< orphan*/  ngx_event_get_peer ; 
 int /*<<< orphan*/  ngx_imap_start ; 
 int /*<<< orphan*/  ngx_mail_core_module ; 
 void* ngx_mail_get_module_srv_conf (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_mail_proxy_block_read ; 
 int /*<<< orphan*/  ngx_mail_proxy_dummy_handler ; 
 int /*<<< orphan*/  ngx_mail_proxy_imap_handler ; 
 int /*<<< orphan*/  ngx_mail_proxy_internal_server_error (TYPE_7__*) ; 
 int /*<<< orphan*/  ngx_mail_proxy_module ; 
 int /*<<< orphan*/  ngx_mail_proxy_pop3_handler ; 
 int /*<<< orphan*/  ngx_mail_proxy_smtp_handler ; 
 int /*<<< orphan*/  ngx_mail_session_internal_server_error (TYPE_7__*) ; 
 TYPE_8__* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_pop3_start ; 
 int /*<<< orphan*/  ngx_smtp_start ; 

void
ngx_mail_proxy_init(ngx_mail_session_t *s, ngx_addr_t *peer)
{
    ngx_int_t                  rc;
    ngx_mail_proxy_ctx_t      *p;
    ngx_mail_proxy_conf_t     *pcf;
    ngx_mail_core_srv_conf_t  *cscf;

    s->connection->log->action = "connecting to upstream";

    cscf = ngx_mail_get_module_srv_conf(s, ngx_mail_core_module);

    p = ngx_pcalloc(s->connection->pool, sizeof(ngx_mail_proxy_ctx_t));
    if (p == NULL) {
        ngx_mail_session_internal_server_error(s);
        return;
    }

    s->proxy = p;

    p->upstream.sockaddr = peer->sockaddr;
    p->upstream.socklen = peer->socklen;
    p->upstream.name = &peer->name;
    p->upstream.get = ngx_event_get_peer;
    p->upstream.log = s->connection->log;
    p->upstream.log_error = NGX_ERROR_ERR;

    rc = ngx_event_connect_peer(&p->upstream);

    if (rc == NGX_ERROR || rc == NGX_BUSY || rc == NGX_DECLINED) {
        ngx_mail_proxy_internal_server_error(s);
        return;
    }

    ngx_add_timer(p->upstream.connection->read, cscf->timeout);

    p->upstream.connection->data = s;
    p->upstream.connection->pool = s->connection->pool;

    s->connection->read->handler = ngx_mail_proxy_block_read;
    p->upstream.connection->write->handler = ngx_mail_proxy_dummy_handler;

    pcf = ngx_mail_get_module_srv_conf(s, ngx_mail_proxy_module);

    s->proxy->buffer = ngx_create_temp_buf(s->connection->pool,
                                           pcf->buffer_size);
    if (s->proxy->buffer == NULL) {
        ngx_mail_proxy_internal_server_error(s);
        return;
    }

    s->out.len = 0;

    switch (s->protocol) {

    case NGX_MAIL_POP3_PROTOCOL:
        p->upstream.connection->read->handler = ngx_mail_proxy_pop3_handler;
        s->mail_state = ngx_pop3_start;
        break;

    case NGX_MAIL_IMAP_PROTOCOL:
        p->upstream.connection->read->handler = ngx_mail_proxy_imap_handler;
        s->mail_state = ngx_imap_start;
        break;

    default: /* NGX_MAIL_SMTP_PROTOCOL */
        p->upstream.connection->read->handler = ngx_mail_proxy_smtp_handler;
        s->mail_state = ngx_smtp_start;
        break;
    }
}