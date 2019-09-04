#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* hw; } ;
struct mt76x0_dev {int /*<<< orphan*/  debugfs_reg; TYPE_3__ mt76; } ;
struct dentry {int dummy; } ;
struct TYPE_5__ {TYPE_1__* wiphy; } ;
struct TYPE_4__ {int /*<<< orphan*/  debugfsdir; } ;

/* Variables and functions */
 int S_IRUSR ; 
 int S_IWUSR ; 
 struct dentry* debugfs_create_dir (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,struct dentry*,struct mt76x0_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_u32 (char*,int,struct dentry*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fops_ampdu_stat ; 
 int /*<<< orphan*/  fops_eeprom_param ; 
 int /*<<< orphan*/  fops_regval ; 

void mt76x0_init_debugfs(struct mt76x0_dev *dev)
{
	struct dentry *dir;

	dir = debugfs_create_dir("mt76x0", dev->mt76.hw->wiphy->debugfsdir);
	if (!dir)
		return;

	debugfs_create_u32("regidx", S_IRUSR | S_IWUSR, dir, &dev->debugfs_reg);
	debugfs_create_file("regval", S_IRUSR | S_IWUSR, dir, dev,
			    &fops_regval);
	debugfs_create_file("ampdu_stat", S_IRUSR, dir, dev, &fops_ampdu_stat);
	debugfs_create_file("eeprom_param", S_IRUSR, dir, dev,
			    &fops_eeprom_param);
}