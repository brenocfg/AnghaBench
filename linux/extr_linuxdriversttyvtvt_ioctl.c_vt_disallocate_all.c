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
 int MAX_NR_CONSOLES ; 
 int MIN_NR_CONSOLES ; 
 int /*<<< orphan*/  VT_BUSY (int) ; 
 int /*<<< orphan*/  console_lock () ; 
 int /*<<< orphan*/  console_unlock () ; 
 int /*<<< orphan*/  kfree (struct vc_data*) ; 
 int /*<<< orphan*/  tty_port_destroy (int /*<<< orphan*/ *) ; 
 struct vc_data* vc_deallocate (int) ; 

__attribute__((used)) static void vt_disallocate_all(void)
{
	struct vc_data *vc[MAX_NR_CONSOLES];
	int i;

	console_lock();
	for (i = 1; i < MAX_NR_CONSOLES; i++)
		if (!VT_BUSY(i))
			vc[i] = vc_deallocate(i);
		else
			vc[i] = NULL;
	console_unlock();

	for (i = 1; i < MAX_NR_CONSOLES; i++) {
		if (vc[i] && i >= MIN_NR_CONSOLES) {
			tty_port_destroy(&vc[i]->port);
			kfree(vc[i]);
		}
	}
}