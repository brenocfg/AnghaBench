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
typedef  int /*<<< orphan*/  u16 ;
struct regs {int /*<<< orphan*/  reg; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_stat_reg_addr(const struct regs *regs, int size,
			     const char *name, u16 *reg_addr)
{
	int i;

	for (i = 0; i < size; i++) {
		if (!strcmp(name, regs[i].name)) {
			*reg_addr = regs[i].reg;
			return 0;
		}
	}
	return -EFAULT;
}