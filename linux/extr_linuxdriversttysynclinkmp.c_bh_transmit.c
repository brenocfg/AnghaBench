#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {int dummy; } ;
struct TYPE_4__ {struct tty_struct* tty; } ;
struct TYPE_5__ {int /*<<< orphan*/  device_name; TYPE_1__ port; } ;
typedef  TYPE_2__ SLMP_INFO ;

/* Variables and functions */
 scalar_t__ DEBUG_LEVEL_BH ; 
 scalar_t__ debug_level ; 
 int /*<<< orphan*/  printk (char*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_wakeup (struct tty_struct*) ; 

__attribute__((used)) static void bh_transmit(SLMP_INFO *info)
{
	struct tty_struct *tty = info->port.tty;

	if ( debug_level >= DEBUG_LEVEL_BH )
		printk( "%s(%d):%s bh_transmit() entry\n",
			__FILE__,__LINE__,info->device_name);

	if (tty)
		tty_wakeup(tty);
}