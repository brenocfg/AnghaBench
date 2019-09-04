#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct dgnc_board {int boardnum; TYPE_2__* serial_driver; TYPE_1__* pdev; TYPE_2__* print_driver; int /*<<< orphan*/  maxports; int /*<<< orphan*/  print_name; int /*<<< orphan*/  serial_name; } ;
struct TYPE_6__ {int /*<<< orphan*/  major; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (TYPE_2__*) ; 
 int /*<<< orphan*/  MAXTTYNAMELEN ; 
 int PTR_ERR (TYPE_2__*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 void* dgnc_tty_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dgnc_tty_free (TYPE_2__*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

int dgnc_tty_register(struct dgnc_board *brd)
{
	int rc;

	snprintf(brd->serial_name, MAXTTYNAMELEN, "tty_dgnc_%d_",
		 brd->boardnum);

	brd->serial_driver = dgnc_tty_create(brd->serial_name,
					     brd->maxports, 0, 0);
	if (IS_ERR(brd->serial_driver)) {
		rc = PTR_ERR(brd->serial_driver);
		dev_dbg(&brd->pdev->dev, "Can't register tty device (%d)\n",
			rc);
		return rc;
	}

	snprintf(brd->print_name, MAXTTYNAMELEN, "pr_dgnc_%d_", brd->boardnum);
	brd->print_driver = dgnc_tty_create(brd->print_name, brd->maxports,
					    0x80,
					    brd->serial_driver->major);
	if (IS_ERR(brd->print_driver)) {
		rc = PTR_ERR(brd->print_driver);
		dev_dbg(&brd->pdev->dev,
			"Can't register Transparent Print device(%d)\n", rc);
		dgnc_tty_free(brd->serial_driver);
		return rc;
	}
	return 0;
}