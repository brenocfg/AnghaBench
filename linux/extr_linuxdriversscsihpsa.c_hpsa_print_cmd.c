#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct ctlr_info {TYPE_4__* pdev; } ;
struct TYPE_6__ {int /*<<< orphan*/ * LunAddrBytes; } ;
struct TYPE_7__ {TYPE_2__ LUN; } ;
struct TYPE_5__ {int /*<<< orphan*/ * CDB; } ;
struct CommandList {TYPE_3__ Header; TYPE_1__ Request; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void hpsa_print_cmd(struct ctlr_info *h, char *txt,
				struct CommandList *c)
{
	const u8 *cdb = c->Request.CDB;
	const u8 *lun = c->Header.LUN.LunAddrBytes;

	dev_warn(&h->pdev->dev, "%s: LUN:%8phN CDB:%16phN\n",
		 txt, lun, cdb);
}