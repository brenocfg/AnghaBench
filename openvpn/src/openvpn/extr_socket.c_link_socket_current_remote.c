#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; } ;
struct link_socket_info {struct link_socket_addr* lsa; } ;
struct TYPE_14__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_13__ {TYPE_6__ sin_addr; } ;
struct TYPE_11__ {scalar_t__ sa_family; } ;
struct TYPE_15__ {TYPE_5__ in4; TYPE_3__ sa; } ;
struct TYPE_12__ {TYPE_7__ addr; } ;
struct TYPE_16__ {TYPE_4__ dest; } ;
struct link_socket_addr {TYPE_2__* current_remote; TYPE_8__ actual; } ;
typedef  int /*<<< orphan*/  in_addr_t ;
struct TYPE_10__ {scalar_t__ ai_addr; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int /*<<< orphan*/  IPV4_INVALID_ADDR ; 
 scalar_t__ link_socket_actual_defined (TYPE_8__*) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 

in_addr_t
link_socket_current_remote(const struct link_socket_info *info)
{
    const struct link_socket_addr *lsa = info->lsa;

/*
 * This logic supports "redirect-gateway" semantic, which
 * makes sense only for PF_INET routes over PF_INET endpoints
 *
 * Maybe in the future consider PF_INET6 endpoints also ...
 * by now just ignore it
 *
 * For --remote entries with multiple addresses this
 * only return the actual endpoint we have successfully connected to
 */
    if (lsa->actual.dest.addr.sa.sa_family != AF_INET)
    {
        return IPV4_INVALID_ADDR;
    }

    if (link_socket_actual_defined(&lsa->actual))
    {
        return ntohl(lsa->actual.dest.addr.in4.sin_addr.s_addr);
    }
    else if (lsa->current_remote)
    {
        return ntohl(((struct sockaddr_in *)lsa->current_remote->ai_addr)
                     ->sin_addr.s_addr);
    }
    else
    {
        return 0;
    }
}