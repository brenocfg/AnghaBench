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
struct tty3270 {int /*<<< orphan*/  view; int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int /*<<< orphan*/  raw3270_put_view (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_port_tty_hangup (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
tty3270_hangup_tasklet(struct tty3270 *tp)
{
	tty_port_tty_hangup(&tp->port, true);
	raw3270_put_view(&tp->view);
}