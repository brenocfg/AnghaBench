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
typedef  int /*<<< orphan*/  u8 ;
struct inode {int dummy; } ;
struct file {int dummy; } ;
struct d7s {int /*<<< orphan*/  regs; scalar_t__ flipped; } ;

/* Variables and functions */
 int /*<<< orphan*/  D7S_FLIP ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 struct d7s* d7s_device ; 
 int /*<<< orphan*/  d7s_users ; 
 int /*<<< orphan*/  readb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sol_compat ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int d7s_release(struct inode *inode, struct file *f)
{
	/* Reset flipped state to OBP default only if
	 * no other users have the device open and we
	 * are not operating in solaris-compat mode
	 */
	if (atomic_dec_and_test(&d7s_users) && !sol_compat) {
		struct d7s *p = d7s_device;
		u8 regval = 0;

		regval = readb(p->regs);
		if (p->flipped)
			regval |= D7S_FLIP;
		else
			regval &= ~D7S_FLIP;
		writeb(regval, p->regs);
	}

	return 0;
}