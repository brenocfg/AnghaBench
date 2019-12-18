#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct in6_addr {int dummy; } ;
struct sockaddr_in6 {struct in6_addr const sin6_addr; } ;
struct link_socket_info {struct link_socket_addr* lsa; } ;
struct TYPE_11__ {struct in6_addr const sin6_addr; } ;
struct TYPE_8__ {scalar_t__ sa_family; } ;
struct TYPE_9__ {TYPE_5__ in6; TYPE_2__ sa; } ;
struct TYPE_10__ {TYPE_3__ addr; } ;
struct TYPE_12__ {TYPE_4__ dest; } ;
struct link_socket_addr {TYPE_1__* current_remote; TYPE_6__ actual; } ;
struct TYPE_7__ {scalar_t__ ai_addr; } ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 scalar_t__ link_socket_actual_defined (TYPE_6__*) ; 

const struct in6_addr *
link_socket_current_remote_ipv6(const struct link_socket_info *info)
{
    const struct link_socket_addr *lsa = info->lsa;

/* This logic supports "redirect-gateway" semantic,
 * for PF_INET6 routes over PF_INET6 endpoints
 *
 * For --remote entries with multiple addresses this
 * only return the actual endpoint we have successfully connected to
 */
    if (lsa->actual.dest.addr.sa.sa_family != AF_INET6)
    {
        return NULL;
    }

    if (link_socket_actual_defined(&lsa->actual))
    {
        return &(lsa->actual.dest.addr.in6.sin6_addr);
    }
    else if (lsa->current_remote)
    {
        return &(((struct sockaddr_in6 *)lsa->current_remote->ai_addr)->sin6_addr);
    }
    else
    {
        return NULL;
    }
}