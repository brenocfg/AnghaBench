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
struct rfkill {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rfkill_destroy (struct rfkill*) ; 
 int /*<<< orphan*/  rfkill_unregister (struct rfkill*) ; 

__attribute__((used)) static inline void __oaktrail_rfkill_cleanup(struct rfkill *rf)
{
	if (rf) {
		rfkill_unregister(rf);
		rfkill_destroy(rf);
	}
}