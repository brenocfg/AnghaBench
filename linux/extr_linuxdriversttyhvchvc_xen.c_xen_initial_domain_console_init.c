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
struct xencons_info {int /*<<< orphan*/  list; int /*<<< orphan*/  vtermno; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HVC_COOKIE ; 
 int /*<<< orphan*/  VIRQ_CONSOLE ; 
 int /*<<< orphan*/  bind_virq_to_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct xencons_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct xencons_info* vtermno_to_xencons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xen_initial_domain () ; 
 int /*<<< orphan*/  xencons_lock ; 
 int /*<<< orphan*/  xenconsoles ; 

__attribute__((used)) static int xen_initial_domain_console_init(void)
{
	struct xencons_info *info;

	if (!xen_initial_domain())
		return -ENODEV;

	info = vtermno_to_xencons(HVC_COOKIE);
	if (!info) {
		info = kzalloc(sizeof(struct xencons_info), GFP_KERNEL);
		if (!info)
			return -ENOMEM;
	}

	info->irq = bind_virq_to_irq(VIRQ_CONSOLE, 0, false);
	info->vtermno = HVC_COOKIE;

	spin_lock(&xencons_lock);
	list_add_tail(&info->list, &xenconsoles);
	spin_unlock(&xencons_lock);

	return 0;
}