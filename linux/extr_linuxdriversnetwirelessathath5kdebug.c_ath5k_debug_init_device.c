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
struct dentry {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  level; } ;
struct ath5k_hw {int /*<<< orphan*/  ah_use_32khz_clock; TYPE_3__* hw; TYPE_1__ debug; } ;
struct TYPE_6__ {TYPE_2__* wiphy; } ;
struct TYPE_5__ {int /*<<< orphan*/  debugfsdir; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath5k_debug ; 
 int /*<<< orphan*/  debugfs_create_bool (char*,int,struct dentry*,int /*<<< orphan*/ *) ; 
 struct dentry* debugfs_create_dir (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,struct dentry*,struct ath5k_hw*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fops_ani ; 
 int /*<<< orphan*/  fops_antenna ; 
 int /*<<< orphan*/  fops_beacon ; 
 int /*<<< orphan*/  fops_debug ; 
 int /*<<< orphan*/  fops_eeprom ; 
 int /*<<< orphan*/  fops_frameerrors ; 
 int /*<<< orphan*/  fops_misc ; 
 int /*<<< orphan*/  fops_queue ; 
 int /*<<< orphan*/  fops_registers ; 
 int /*<<< orphan*/  fops_reset ; 

void
ath5k_debug_init_device(struct ath5k_hw *ah)
{
	struct dentry *phydir;

	ah->debug.level = ath5k_debug;

	phydir = debugfs_create_dir("ath5k", ah->hw->wiphy->debugfsdir);
	if (!phydir)
		return;

	debugfs_create_file("debug", 0600, phydir, ah, &fops_debug);
	debugfs_create_file("registers", 0400, phydir, ah, &fops_registers);
	debugfs_create_file("beacon", 0600, phydir, ah, &fops_beacon);
	debugfs_create_file("reset", 0200, phydir, ah, &fops_reset);
	debugfs_create_file("antenna", 0600, phydir, ah, &fops_antenna);
	debugfs_create_file("misc", 0400, phydir, ah, &fops_misc);
	debugfs_create_file("eeprom", 0400, phydir, ah, &fops_eeprom);
	debugfs_create_file("frameerrors", 0600, phydir, ah, &fops_frameerrors);
	debugfs_create_file("ani", 0600, phydir, ah, &fops_ani);
	debugfs_create_file("queue", 0600, phydir, ah, &fops_queue);
	debugfs_create_bool("32khz_clock", 0600, phydir,
			    &ah->ah_use_32khz_clock);
}