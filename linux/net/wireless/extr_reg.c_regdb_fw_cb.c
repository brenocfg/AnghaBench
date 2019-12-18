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
struct firmware {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODATA ; 
 void* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_ERR (void*) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kmemdup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 scalar_t__ query_regdb (void*) ; 
 void* regdb ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int /*<<< orphan*/  restore_regulatory_settings (int,int) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  valid_regdb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void regdb_fw_cb(const struct firmware *fw, void *context)
{
	int set_error = 0;
	bool restore = true;
	void *db;

	if (!fw) {
		pr_info("failed to load regulatory.db\n");
		set_error = -ENODATA;
	} else if (!valid_regdb(fw->data, fw->size)) {
		pr_info("loaded regulatory.db is malformed or signature is missing/invalid\n");
		set_error = -EINVAL;
	}

	rtnl_lock();
	if (regdb && !IS_ERR(regdb)) {
		/* negative case - a bug
		 * positive case - can happen due to race in case of multiple cb's in
		 * queue, due to usage of asynchronous callback
		 *
		 * Either case, just restore and free new db.
		 */
	} else if (set_error) {
		regdb = ERR_PTR(set_error);
	} else if (fw) {
		db = kmemdup(fw->data, fw->size, GFP_KERNEL);
		if (db) {
			regdb = db;
			restore = context && query_regdb(context);
		} else {
			restore = true;
		}
	}

	if (restore)
		restore_regulatory_settings(true, false);

	rtnl_unlock();

	kfree(context);

	release_firmware(fw);
}