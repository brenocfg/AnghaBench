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
struct tps6524x {int dummy; } ;
struct field {int shift; int mask; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int read_reg (struct tps6524x*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int read_field(struct tps6524x *hw, const struct field *field)
{
	int tmp;

	tmp = read_reg(hw, field->reg);
	if (tmp < 0)
		return tmp;

	return (tmp >> field->shift) & field->mask;
}