#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  scalar_t__ ngx_uint_t ;
struct TYPE_4__ {int facility; int /*<<< orphan*/  tag; scalar_t__ nohostname; scalar_t__ severity; } ;
typedef  TYPE_1__ ngx_syslog_peer_t ;
struct TYPE_5__ {int /*<<< orphan*/  hostname; } ;

/* Variables and functions */
 int /*<<< orphan*/  ngx_cached_syslog_time ; 
 TYPE_3__* ngx_cycle ; 
 int /*<<< orphan*/ * ngx_sprintf (int /*<<< orphan*/ *,char*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,...) ; 

u_char *
ngx_syslog_add_header(ngx_syslog_peer_t *peer, u_char *buf)
{
    ngx_uint_t  pri;

    pri = peer->facility * 8 + peer->severity;

    if (peer->nohostname) {
        return ngx_sprintf(buf, "<%ui>%V %V: ", pri, &ngx_cached_syslog_time,
                           &peer->tag);
    }

    return ngx_sprintf(buf, "<%ui>%V %V %V: ", pri, &ngx_cached_syslog_time,
                       &ngx_cycle->hostname, &peer->tag);
}