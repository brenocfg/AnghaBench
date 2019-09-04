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
struct rtsx_dev {int /*<<< orphan*/  reg_lock; } ;
struct rtsx_chip {struct rtsx_dev* rtsx; } ;

/* Variables and functions */
 int /*<<< orphan*/  rtsx_enter_ss (struct rtsx_chip*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void rtsx_exclusive_enter_ss(struct rtsx_chip *chip)
{
	struct rtsx_dev *dev = chip->rtsx;

	spin_lock(&dev->reg_lock);
	rtsx_enter_ss(chip);
	spin_unlock(&dev->reg_lock);
}