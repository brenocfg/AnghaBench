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
struct TYPE_2__ {int /*<<< orphan*/  frame; int /*<<< orphan*/  link_socket; } ;
struct context {int /*<<< orphan*/  sig; TYPE_1__ c2; } ;

/* Variables and functions */
 int /*<<< orphan*/  link_socket_init_phase2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
do_init_socket_2(struct context *c)
{
    link_socket_init_phase2(c->c2.link_socket, &c->c2.frame,
                            c->sig);
}