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
struct zcrypt_card {TYPE_3__* card; int /*<<< orphan*/  list; } ;
struct TYPE_4__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_5__ {TYPE_1__ device; } ;
struct TYPE_6__ {TYPE_2__ ap_dev; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBF_INFO ; 
 int /*<<< orphan*/  ZCRYPT_DBF (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zcrypt_card_attr_group ; 
 int /*<<< orphan*/  zcrypt_list_lock ; 

void zcrypt_card_unregister(struct zcrypt_card *zc)
{
	ZCRYPT_DBF(DBF_INFO, "card=%02x unregister\n", zc->card->id);

	spin_lock(&zcrypt_list_lock);
	list_del_init(&zc->list);
	spin_unlock(&zcrypt_list_lock);
	sysfs_remove_group(&zc->card->ap_dev.device.kobj,
			   &zcrypt_card_attr_group);
}