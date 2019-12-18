#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct sockaddr {int sa_family; } ;
typedef  struct sockaddr u_char ;
typedef  size_t socklen_t ;
typedef  scalar_t__ ngx_socket_t ;
struct TYPE_10__ {size_t len; struct sockaddr* data; } ;
struct TYPE_11__ {size_t socklen; int addr_text_max_len; int rcvbuf; int sndbuf; int setfib; int fastopen; int /*<<< orphan*/  backlog; int /*<<< orphan*/  type; scalar_t__ fd; int /*<<< orphan*/  sentinel; int /*<<< orphan*/  rbtree; TYPE_2__ addr_text; struct sockaddr* sockaddr; } ;
typedef  TYPE_3__ ngx_listening_t ;
struct TYPE_12__ {int /*<<< orphan*/  pool; TYPE_1__* cycle; } ;
typedef  TYPE_4__ ngx_conf_t ;
struct TYPE_9__ {int /*<<< orphan*/  listening; } ;

/* Variables and functions */
#define  AF_INET 130 
#define  AF_INET6 129 
#define  AF_UNIX 128 
 int NGX_INET6_ADDRSTRLEN ; 
 int NGX_INET_ADDRSTRLEN ; 
 int /*<<< orphan*/  NGX_LISTEN_BACKLOG ; 
 int NGX_SOCKADDR_STRLEN ; 
 int NGX_UNIX_ADDRSTRLEN ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 TYPE_3__* ngx_array_push (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_memcpy (struct sockaddr*,struct sockaddr*,size_t) ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_3__*,int) ; 
 struct sockaddr* ngx_palloc (int /*<<< orphan*/ ,size_t) ; 
 struct sockaddr* ngx_pnalloc (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  ngx_rbtree_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t ngx_sock_ntop (struct sockaddr*,size_t,struct sockaddr*,int,int) ; 
 int /*<<< orphan*/  ngx_udp_rbtree_insert_value ; 

ngx_listening_t *
ngx_create_listening(ngx_conf_t *cf, struct sockaddr *sockaddr,
    socklen_t socklen)
{
    size_t            len;
    ngx_listening_t  *ls;
    struct sockaddr  *sa;
    u_char            text[NGX_SOCKADDR_STRLEN];

    ls = ngx_array_push(&cf->cycle->listening);
    if (ls == NULL) {
        return NULL;
    }

    ngx_memzero(ls, sizeof(ngx_listening_t));

    sa = ngx_palloc(cf->pool, socklen);
    if (sa == NULL) {
        return NULL;
    }

    ngx_memcpy(sa, sockaddr, socklen);

    ls->sockaddr = sa;
    ls->socklen = socklen;

    len = ngx_sock_ntop(sa, socklen, text, NGX_SOCKADDR_STRLEN, 1);
    ls->addr_text.len = len;

    switch (ls->sockaddr->sa_family) {
#if (NGX_HAVE_INET6)
    case AF_INET6:
        ls->addr_text_max_len = NGX_INET6_ADDRSTRLEN;
        break;
#endif
#if (NGX_HAVE_UNIX_DOMAIN)
    case AF_UNIX:
        ls->addr_text_max_len = NGX_UNIX_ADDRSTRLEN;
        len++;
        break;
#endif
    case AF_INET:
        ls->addr_text_max_len = NGX_INET_ADDRSTRLEN;
        break;
    default:
        ls->addr_text_max_len = NGX_SOCKADDR_STRLEN;
        break;
    }

    ls->addr_text.data = ngx_pnalloc(cf->pool, len);
    if (ls->addr_text.data == NULL) {
        return NULL;
    }

    ngx_memcpy(ls->addr_text.data, text, len);

#if !(NGX_WIN32)
    ngx_rbtree_init(&ls->rbtree, &ls->sentinel, ngx_udp_rbtree_insert_value);
#endif

    ls->fd = (ngx_socket_t) -1;
    ls->type = SOCK_STREAM;

    ls->backlog = NGX_LISTEN_BACKLOG;
    ls->rcvbuf = -1;
    ls->sndbuf = -1;

#if (NGX_HAVE_SETFIB)
    ls->setfib = -1;
#endif

#if (NGX_HAVE_TCP_FASTOPEN)
    ls->fastopen = -1;
#endif

    return ls;
}