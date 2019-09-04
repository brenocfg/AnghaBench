#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sockaddr {int dummy; } ;
struct TYPE_6__ {TYPE_1__* url; } ;
typedef  TYPE_2__ ngx_rtmp_netcall_session_t ;
struct TYPE_7__ {int /*<<< orphan*/ * name; int /*<<< orphan*/  socklen; struct sockaddr* sockaddr; } ;
typedef  TYPE_3__ ngx_peer_connection_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_5__ {int /*<<< orphan*/  host; int /*<<< orphan*/  socklen; int /*<<< orphan*/  sockaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_OK ; 

__attribute__((used)) static ngx_int_t
ngx_rtmp_netcall_get_peer(ngx_peer_connection_t *pc, void *data)
{
    ngx_rtmp_netcall_session_t   *cs = data;

    pc->sockaddr =(struct sockaddr *)&cs->url->sockaddr;
    pc->socklen = cs->url->socklen;
    pc->name = &cs->url->host;

    return NGX_OK;
}