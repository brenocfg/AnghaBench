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
struct pcistub_device {int dummy; } ;

/* Variables and functions */
 struct pcistub_device* pcistub_device_find_locked (int,int,int,int) ; 
 int /*<<< orphan*/  pcistub_device_get (struct pcistub_device*) ; 
 int /*<<< orphan*/  pcistub_devices_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct pcistub_device *pcistub_device_find(int domain, int bus,
						  int slot, int func)
{
	struct pcistub_device *psdev;
	unsigned long flags;

	spin_lock_irqsave(&pcistub_devices_lock, flags);

	psdev = pcistub_device_find_locked(domain, bus, slot, func);
	if (psdev)
		pcistub_device_get(psdev);

	spin_unlock_irqrestore(&pcistub_devices_lock, flags);
	return psdev;
}