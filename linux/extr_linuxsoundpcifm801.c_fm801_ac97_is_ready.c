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
struct fm801 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_CMD ; 
 int FM801_AC97_BUSY ; 
 int fm801_readw (struct fm801*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static bool fm801_ac97_is_ready(struct fm801 *chip, unsigned int iterations)
{
	unsigned int idx;

	for (idx = 0; idx < iterations; idx++) {
		if (!(fm801_readw(chip, AC97_CMD) & FM801_AC97_BUSY))
			return true;
		udelay(10);
	}
	return false;
}