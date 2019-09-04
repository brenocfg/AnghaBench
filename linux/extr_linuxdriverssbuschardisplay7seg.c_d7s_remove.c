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
struct platform_device {int /*<<< orphan*/ * resource; int /*<<< orphan*/  dev; } ;
struct d7s {int /*<<< orphan*/  regs; scalar_t__ flipped; } ;

/* Variables and functions */
 int /*<<< orphan*/  D7S_FLIP ; 
 int /*<<< orphan*/  d7s_miscdev ; 
 struct d7s* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  misc_deregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_iounmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  readb (int /*<<< orphan*/ ) ; 
 scalar_t__ sol_compat ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int d7s_remove(struct platform_device *op)
{
	struct d7s *p = dev_get_drvdata(&op->dev);
	u8 regs = readb(p->regs);

	/* Honor OBP d7s-flipped? unless operating in solaris-compat mode */
	if (sol_compat) {
		if (p->flipped)
			regs |= D7S_FLIP;
		else
			regs &= ~D7S_FLIP;
		writeb(regs, p->regs);
	}

	misc_deregister(&d7s_miscdev);
	of_iounmap(&op->resource[0], p->regs, sizeof(u8));

	return 0;
}