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
struct iss_device {scalar_t__ ref_count; int /*<<< orphan*/  iss_mutex; int /*<<< orphan*/  crashed; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  iss_disable_clocks (struct iss_device*) ; 
 int /*<<< orphan*/  iss_disable_interrupts (struct iss_device*) ; 
 int /*<<< orphan*/  iss_reset (struct iss_device*) ; 
 int /*<<< orphan*/  media_entity_enum_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void omap4iss_put(struct iss_device *iss)
{
	if (!iss)
		return;

	mutex_lock(&iss->iss_mutex);
	WARN_ON(iss->ref_count == 0);
	if (--iss->ref_count == 0) {
		iss_disable_interrupts(iss);
		/* Reset the ISS if an entity has failed to stop. This is the
		 * only way to recover from such conditions, although it would
		 * be worth investigating whether resetting the ISP only can't
		 * fix the problem in some cases.
		 */
		if (!media_entity_enum_empty(&iss->crashed))
			iss_reset(iss);
		iss_disable_clocks(iss);
	}
	mutex_unlock(&iss->iss_mutex);
}