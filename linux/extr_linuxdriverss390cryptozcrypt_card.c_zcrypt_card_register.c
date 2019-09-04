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
struct zcrypt_card {int online; TYPE_3__* card; int /*<<< orphan*/  list; } ;
struct TYPE_4__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_5__ {TYPE_1__ device; } ;
struct TYPE_6__ {int /*<<< orphan*/  id; TYPE_2__ ap_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBF_INFO ; 
 int /*<<< orphan*/  ZCRYPT_DBF (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zcrypt_card_attr_group ; 
 int /*<<< orphan*/  zcrypt_card_list ; 
 int /*<<< orphan*/  zcrypt_list_lock ; 

int zcrypt_card_register(struct zcrypt_card *zc)
{
	int rc;

	rc = sysfs_create_group(&zc->card->ap_dev.device.kobj,
				&zcrypt_card_attr_group);
	if (rc)
		return rc;

	spin_lock(&zcrypt_list_lock);
	list_add_tail(&zc->list, &zcrypt_card_list);
	spin_unlock(&zcrypt_list_lock);

	zc->online = 1;

	ZCRYPT_DBF(DBF_INFO, "card=%02x register online=1\n", zc->card->id);

	return rc;
}