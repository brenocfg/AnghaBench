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
struct riowd {int /*<<< orphan*/  regs; int /*<<< orphan*/  lock; } ;
struct platform_device {int /*<<< orphan*/ * resource; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_NAME ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct riowd* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int misc_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_ioremap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_iounmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct riowd*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct riowd* riowd_device ; 
 int /*<<< orphan*/  riowd_miscdev ; 
 int /*<<< orphan*/  riowd_timeout ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int riowd_probe(struct platform_device *op)
{
	struct riowd *p;
	int err = -EINVAL;

	if (riowd_device)
		goto out;

	err = -ENOMEM;
	p = devm_kzalloc(&op->dev, sizeof(*p), GFP_KERNEL);
	if (!p)
		goto out;

	spin_lock_init(&p->lock);

	p->regs = of_ioremap(&op->resource[0], 0, 2, DRIVER_NAME);
	if (!p->regs) {
		pr_err("Cannot map registers\n");
		goto out;
	}
	/* Make miscdev useable right away */
	riowd_device = p;

	err = misc_register(&riowd_miscdev);
	if (err) {
		pr_err("Cannot register watchdog misc device\n");
		goto out_iounmap;
	}

	pr_info("Hardware watchdog [%i minutes], regs at %p\n",
		riowd_timeout, p->regs);

	platform_set_drvdata(op, p);
	return 0;

out_iounmap:
	riowd_device = NULL;
	of_iounmap(&op->resource[0], p->regs, 2);

out:
	return err;
}