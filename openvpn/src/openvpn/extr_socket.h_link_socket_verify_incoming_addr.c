#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct link_socket_info {int /*<<< orphan*/  proto; TYPE_3__* lsa; int /*<<< orphan*/  remote_float; } ;
struct TYPE_5__ {int sa_family; } ;
struct TYPE_6__ {TYPE_1__ sa; } ;
struct TYPE_8__ {TYPE_2__ addr; } ;
struct link_socket_actual {TYPE_4__ dest; } ;
struct buffer {scalar_t__ len; } ;
struct TYPE_7__ {int /*<<< orphan*/  remote_list; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  addrlist_match_proto (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link_socket_actual_defined (struct link_socket_actual const*) ; 

__attribute__((used)) static inline bool
link_socket_verify_incoming_addr(struct buffer *buf,
                                 const struct link_socket_info *info,
                                 const struct link_socket_actual *from_addr)
{
    if (buf->len > 0)
    {
        switch (from_addr->dest.addr.sa.sa_family)
        {
            case AF_INET6:
            case AF_INET:
                if (!link_socket_actual_defined(from_addr))
                {
                    return false;
                }
                if (info->remote_float || (!info->lsa->remote_list))
                {
                    return true;
                }
                if (addrlist_match_proto(&from_addr->dest, info->lsa->remote_list, info->proto))
                {
                    return true;
                }
        }
    }
    return false;
}