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
struct mutex {int dummy; } ;

/* Variables and functions */
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  mutex_unlock (struct mutex*) ; 

__attribute__((used)) static void kcmp_unlock(struct mutex *m1, struct mutex *m2)
{
	if (likely(m2 != m1))
		mutex_unlock(m2);
	mutex_unlock(m1);
}