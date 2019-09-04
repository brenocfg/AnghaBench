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
struct apertures_struct {int dummy; } ;

/* Variables and functions */
 int do_remove_conflicting_framebuffers (struct apertures_struct*,char const*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  registration_lock ; 

int remove_conflicting_framebuffers(struct apertures_struct *a,
				    const char *name, bool primary)
{
	int ret;

	mutex_lock(&registration_lock);
	ret = do_remove_conflicting_framebuffers(a, name, primary);
	mutex_unlock(&registration_lock);

	return ret;
}