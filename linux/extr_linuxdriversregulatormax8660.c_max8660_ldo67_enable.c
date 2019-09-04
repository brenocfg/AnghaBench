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
typedef  int u8 ;
struct regulator_dev {int dummy; } ;
struct max8660 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX8660_OVER2 ; 
 scalar_t__ MAX8660_V6 ; 
 int max8660_write (struct max8660*,int /*<<< orphan*/ ,int,int) ; 
 struct max8660* rdev_get_drvdata (struct regulator_dev*) ; 
 scalar_t__ rdev_get_id (struct regulator_dev*) ; 

__attribute__((used)) static int max8660_ldo67_enable(struct regulator_dev *rdev)
{
	struct max8660 *max8660 = rdev_get_drvdata(rdev);
	u8 bit = (rdev_get_id(rdev) == MAX8660_V6) ? 2 : 4;

	return max8660_write(max8660, MAX8660_OVER2, 0xff, bit);
}