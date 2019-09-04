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
struct regulator_dev {int dummy; } ;
struct max77802_regulator_prv {int /*<<< orphan*/ * opmode; } ;

/* Variables and functions */
 int max77802_map_mode (int /*<<< orphan*/ ) ; 
 struct max77802_regulator_prv* rdev_get_drvdata (struct regulator_dev*) ; 
 int rdev_get_id (struct regulator_dev*) ; 

__attribute__((used)) static unsigned max77802_get_mode(struct regulator_dev *rdev)
{
	struct max77802_regulator_prv *max77802 = rdev_get_drvdata(rdev);
	int id = rdev_get_id(rdev);

	return max77802_map_mode(max77802->opmode[id]);
}