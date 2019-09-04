#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* d; } ;
struct TYPE_4__ {scalar_t__ tty; } ;
struct TYPE_5__ {TYPE_1__ port; } ;

/* Variables and functions */
 int MAX_NR_CONSOLES ; 
 int /*<<< orphan*/  stop_tty (scalar_t__) ; 
 TYPE_3__* vc_cons ; 

__attribute__((used)) static void speakup_stop_ttys(void)
{
	int i;

	for (i = 0; i < MAX_NR_CONSOLES; i++)
		if (vc_cons[i].d && vc_cons[i].d->port.tty)
			stop_tty(vc_cons[i].d->port.tty);
}