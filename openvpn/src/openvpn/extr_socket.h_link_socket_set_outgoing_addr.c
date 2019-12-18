#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct link_socket_info {int /*<<< orphan*/  proto; scalar_t__ remote_float; int /*<<< orphan*/  connection_established; struct link_socket_addr* lsa; } ;
struct TYPE_2__ {int /*<<< orphan*/  dest; } ;
struct link_socket_addr {int /*<<< orphan*/  remote_list; TYPE_1__ actual; } ;
struct link_socket_actual {int /*<<< orphan*/  dest; } ;
struct env_set {int dummy; } ;
struct buffer {scalar_t__ len; } ;

/* Variables and functions */
 int /*<<< orphan*/  addr_match_proto (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ addrlist_match_proto (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link_socket_connection_initiated (struct buffer const*,struct link_socket_info*,struct link_socket_actual const*,char const*,struct env_set*) ; 

__attribute__((used)) static inline void
link_socket_set_outgoing_addr(const struct buffer *buf,
                              struct link_socket_info *info,
                              const struct link_socket_actual *act,
                              const char *common_name,
                              struct env_set *es)
{
    if (!buf || buf->len > 0)
    {
        struct link_socket_addr *lsa = info->lsa;
        if (
            /* new or changed address? */
            (!info->connection_established
             || !addr_match_proto(&act->dest, &lsa->actual.dest, info->proto)
            )
            &&
            /* address undef or address == remote or --float */
            (info->remote_float
             || (!lsa->remote_list || addrlist_match_proto(&act->dest, lsa->remote_list, info->proto))
            )
            )
        {
            link_socket_connection_initiated(buf, info, act, common_name, es);
        }
    }
}