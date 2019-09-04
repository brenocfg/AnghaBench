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
struct lm3630a_chip {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int regmap_write (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static int lm3630a_write(struct lm3630a_chip *pchip,
			 unsigned int reg, unsigned int data)
{
	return regmap_write(pchip->regmap, reg, data);
}