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
struct regulator_dev {scalar_t__ mutex_owner; int ref_cnt; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 scalar_t__ current ; 
 int /*<<< orphan*/  mutex_lock_nested (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  mutex_trylock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void regulator_lock_nested(struct regulator_dev *rdev,
				  unsigned int subclass)
{
	if (!mutex_trylock(&rdev->mutex)) {
		if (rdev->mutex_owner == current) {
			rdev->ref_cnt++;
			return;
		}
		mutex_lock_nested(&rdev->mutex, subclass);
	}

	rdev->ref_cnt = 1;
	rdev->mutex_owner = current;
}