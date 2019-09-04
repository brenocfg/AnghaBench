#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int /*<<< orphan*/  dev; } ;
struct bq4802 {int /*<<< orphan*/  rtc; int /*<<< orphan*/  write; int /*<<< orphan*/  read; int /*<<< orphan*/  regs; TYPE_1__* r; int /*<<< orphan*/  ioport; int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {int flags; int /*<<< orphan*/  start; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IORESOURCE_IO ; 
 int IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  bq4802_ops ; 
 int /*<<< orphan*/  bq4802_read_io ; 
 int /*<<< orphan*/  bq4802_read_mem ; 
 int /*<<< orphan*/  bq4802_write_io ; 
 int /*<<< orphan*/  bq4802_write_mem ; 
 int /*<<< orphan*/  devm_ioremap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bq4802* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_rtc_device_register (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* platform_get_resource (struct platform_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct bq4802*) ; 
 int /*<<< orphan*/  resource_size (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bq4802_probe(struct platform_device *pdev)
{
	struct bq4802 *p = devm_kzalloc(&pdev->dev, sizeof(*p), GFP_KERNEL);
	int err = -ENOMEM;

	if (!p)
		goto out;

	spin_lock_init(&p->lock);

	p->r = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!p->r) {
		p->r = platform_get_resource(pdev, IORESOURCE_IO, 0);
		err = -EINVAL;
		if (!p->r)
			goto out;
	}
	if (p->r->flags & IORESOURCE_IO) {
		p->ioport = p->r->start;
		p->read = bq4802_read_io;
		p->write = bq4802_write_io;
	} else if (p->r->flags & IORESOURCE_MEM) {
		p->regs = devm_ioremap(&pdev->dev, p->r->start,
					resource_size(p->r));
		if (!p->regs){
			err = -ENOMEM;
			goto out;
		}
		p->read = bq4802_read_mem;
		p->write = bq4802_write_mem;
	} else {
		err = -EINVAL;
		goto out;
	}

	platform_set_drvdata(pdev, p);

	p->rtc = devm_rtc_device_register(&pdev->dev, "bq4802",
					&bq4802_ops, THIS_MODULE);
	if (IS_ERR(p->rtc)) {
		err = PTR_ERR(p->rtc);
		goto out;
	}

	err = 0;
out:
	return err;

}