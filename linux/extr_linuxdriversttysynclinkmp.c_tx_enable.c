#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  lock; scalar_t__ tx_enabled; int /*<<< orphan*/  device_name; } ;
typedef  TYPE_1__ SLMP_INFO ;

/* Variables and functions */
 scalar_t__ DEBUG_LEVEL_INFO ; 
 scalar_t__ debug_level ; 
 int /*<<< orphan*/  printk (char*,char*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tx_start (TYPE_1__*) ; 
 int /*<<< orphan*/  tx_stop (TYPE_1__*) ; 

__attribute__((used)) static int tx_enable(SLMP_INFO * info, int enable)
{
 	unsigned long flags;

	if (debug_level >= DEBUG_LEVEL_INFO)
		printk("%s(%d):%s tx_enable(%d)\n",
			__FILE__,__LINE__,info->device_name, enable);

	spin_lock_irqsave(&info->lock,flags);
	if ( enable ) {
		if ( !info->tx_enabled ) {
			tx_start(info);
		}
	} else {
		if ( info->tx_enabled )
			tx_stop(info);
	}
	spin_unlock_irqrestore(&info->lock,flags);
	return 0;
}