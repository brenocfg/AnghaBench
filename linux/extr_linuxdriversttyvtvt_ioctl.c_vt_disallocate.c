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
struct vc_data {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int EBUSY ; 
 unsigned int MIN_NR_CONSOLES ; 
 scalar_t__ VT_BUSY (unsigned int) ; 
 int /*<<< orphan*/  console_lock () ; 
 int /*<<< orphan*/  console_unlock () ; 
 int /*<<< orphan*/  kfree (struct vc_data*) ; 
 int /*<<< orphan*/  tty_port_destroy (int /*<<< orphan*/ *) ; 
 struct vc_data* vc_deallocate (unsigned int) ; 

__attribute__((used)) static int vt_disallocate(unsigned int vc_num)
{
	struct vc_data *vc = NULL;
	int ret = 0;

	console_lock();
	if (VT_BUSY(vc_num))
		ret = -EBUSY;
	else if (vc_num)
		vc = vc_deallocate(vc_num);
	console_unlock();

	if (vc && vc_num >= MIN_NR_CONSOLES) {
		tty_port_destroy(&vc->port);
		kfree(vc);
	}

	return ret;
}