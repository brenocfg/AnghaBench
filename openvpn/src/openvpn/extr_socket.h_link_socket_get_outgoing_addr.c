#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct link_socket_info {struct link_socket_addr* lsa; } ;
struct link_socket_actual {int dummy; } ;
struct link_socket_addr {struct link_socket_actual actual; } ;
struct buffer {scalar_t__ len; } ;

/* Variables and functions */
 scalar_t__ link_socket_actual_defined (struct link_socket_actual*) ; 
 int /*<<< orphan*/  link_socket_bad_outgoing_addr () ; 

__attribute__((used)) static inline void
link_socket_get_outgoing_addr(struct buffer *buf,
                              const struct link_socket_info *info,
                              struct link_socket_actual **act)
{
    if (buf->len > 0)
    {
        struct link_socket_addr *lsa = info->lsa;
        if (link_socket_actual_defined(&lsa->actual))
        {
            *act = &lsa->actual;
        }
        else
        {
            link_socket_bad_outgoing_addr();
            buf->len = 0;
            *act = NULL;
        }
    }
}