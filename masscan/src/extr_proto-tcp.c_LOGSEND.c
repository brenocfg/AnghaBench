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
struct TCP_Control_Block {int /*<<< orphan*/  tcpstate; int /*<<< orphan*/  port_them; int /*<<< orphan*/  ip_them; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOGip (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  state_to_string (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
LOGSEND(struct TCP_Control_Block *tcb, const char *what)
{
    if (tcb == NULL)
        return;
    LOGip(5, tcb->ip_them, tcb->port_them, "=%s : --->> %s                  \n",
          state_to_string(tcb->tcpstate),
          what);
}