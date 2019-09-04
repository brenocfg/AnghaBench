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
struct sl811 {int port1; scalar_t__ jiffies_a; int /*<<< orphan*/ * active_a; } ;

/* Variables and functions */
 scalar_t__ MIN_JIFFIES ; 
 int /*<<< orphan*/  SL811_EP_A (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SL811_HOST_BUF ; 
 int USB_PORT_STAT_SUSPEND ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/ * start (struct sl811*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void start_transfer(struct sl811 *sl811)
{
	if (sl811->port1 & USB_PORT_STAT_SUSPEND)
		return;
	if (sl811->active_a == NULL) {
		sl811->active_a = start(sl811, SL811_EP_A(SL811_HOST_BUF));
		if (sl811->active_a != NULL)
			sl811->jiffies_a = jiffies + MIN_JIFFIES;
	}
#ifdef USE_B
	if (sl811->active_b == NULL) {
		sl811->active_b = start(sl811, SL811_EP_B(SL811_HOST_BUF));
		if (sl811->active_b != NULL)
			sl811->jiffies_b = jiffies + MIN_JIFFIES;
	}
#endif
}