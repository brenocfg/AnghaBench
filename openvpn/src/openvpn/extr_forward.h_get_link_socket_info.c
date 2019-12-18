#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct link_socket_info {int dummy; } ;
struct TYPE_4__ {TYPE_1__* link_socket; struct link_socket_info* link_socket_info; } ;
struct context {TYPE_2__ c2; } ;
struct TYPE_3__ {struct link_socket_info info; } ;

/* Variables and functions */

__attribute__((used)) static inline struct link_socket_info *
get_link_socket_info(struct context *c)
{
    if (c->c2.link_socket_info)
    {
        return c->c2.link_socket_info;
    }
    else
    {
        return &c->c2.link_socket->info;
    }
}