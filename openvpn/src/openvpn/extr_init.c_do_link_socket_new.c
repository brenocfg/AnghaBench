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
struct TYPE_2__ {int link_socket_owned; scalar_t__ link_socket; } ;
struct context {TYPE_1__ c2; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ link_socket_new () ; 

__attribute__((used)) static void
do_link_socket_new(struct context *c)
{
    ASSERT(!c->c2.link_socket);
    c->c2.link_socket = link_socket_new();
    c->c2.link_socket_owned = true;
}