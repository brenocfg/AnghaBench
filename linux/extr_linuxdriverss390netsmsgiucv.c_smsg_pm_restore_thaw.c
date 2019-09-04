#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct TYPE_4__ {int msglim; scalar_t__ flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpcmd (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int iucv_path_connect (TYPE_1__*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int iucv_path_connected ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  smsg_handler ; 
 TYPE_1__* smsg_path ; 

__attribute__((used)) static int smsg_pm_restore_thaw(struct device *dev)
{
	int rc;

#ifdef CONFIG_PM_DEBUG
	printk(KERN_WARNING "smsg_pm_restore_thaw\n");
#endif
	if (smsg_path && !iucv_path_connected) {
		memset(smsg_path, 0, sizeof(*smsg_path));
		smsg_path->msglim = 255;
		smsg_path->flags = 0;
		rc = iucv_path_connect(smsg_path, &smsg_handler, "*MSG    ",
				       NULL, NULL, NULL);
#ifdef CONFIG_PM_DEBUG
		if (rc)
			printk(KERN_ERR
			       "iucv_path_connect returned with rc %i\n", rc);
#endif
		if (!rc)
			iucv_path_connected = 1;
		cpcmd("SET SMSG IUCV", NULL, 0, NULL);
	}
	return 0;
}