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
struct scsi_device {int dummy; } ;
struct alua_port_group {scalar_t__ device_id_len; char* device_id_str; int group_id; int tpgs; int /*<<< orphan*/  node; int /*<<< orphan*/  lock; int /*<<< orphan*/  dh_list; int /*<<< orphan*/  rtpg_list; int /*<<< orphan*/  rtpg_work; int /*<<< orphan*/  kref; int /*<<< orphan*/  flags; int /*<<< orphan*/  valid_states; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALUA_DH_NAME ; 
 int /*<<< orphan*/  ALUA_OPTIMIZE_STPG ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct alua_port_group* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  SCSI_ACCESS_STATE_OPTIMAL ; 
 int /*<<< orphan*/  TPGS_SUPPORT_ALL ; 
 struct alua_port_group* alua_find_get_pg (char*,scalar_t__,int) ; 
 int /*<<< orphan*/  alua_rtpg_work ; 
 int /*<<< orphan*/  kfree (struct alua_port_group*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct alua_port_group* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ optimize_stpg ; 
 int /*<<< orphan*/  port_group_list ; 
 int /*<<< orphan*/  port_group_lock ; 
 scalar_t__ scsi_vpd_lun_id (struct scsi_device*,char*,int) ; 
 int /*<<< orphan*/  sdev_printk (int /*<<< orphan*/ ,struct scsi_device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct alua_port_group *alua_alloc_pg(struct scsi_device *sdev,
					     int group_id, int tpgs)
{
	struct alua_port_group *pg, *tmp_pg;

	pg = kzalloc(sizeof(struct alua_port_group), GFP_KERNEL);
	if (!pg)
		return ERR_PTR(-ENOMEM);

	pg->device_id_len = scsi_vpd_lun_id(sdev, pg->device_id_str,
					    sizeof(pg->device_id_str));
	if (pg->device_id_len <= 0) {
		/*
		 * TPGS supported but no device identification found.
		 * Generate private device identification.
		 */
		sdev_printk(KERN_INFO, sdev,
			    "%s: No device descriptors found\n",
			    ALUA_DH_NAME);
		pg->device_id_str[0] = '\0';
		pg->device_id_len = 0;
	}
	pg->group_id = group_id;
	pg->tpgs = tpgs;
	pg->state = SCSI_ACCESS_STATE_OPTIMAL;
	pg->valid_states = TPGS_SUPPORT_ALL;
	if (optimize_stpg)
		pg->flags |= ALUA_OPTIMIZE_STPG;
	kref_init(&pg->kref);
	INIT_DELAYED_WORK(&pg->rtpg_work, alua_rtpg_work);
	INIT_LIST_HEAD(&pg->rtpg_list);
	INIT_LIST_HEAD(&pg->node);
	INIT_LIST_HEAD(&pg->dh_list);
	spin_lock_init(&pg->lock);

	spin_lock(&port_group_lock);
	tmp_pg = alua_find_get_pg(pg->device_id_str, pg->device_id_len,
				  group_id);
	if (tmp_pg) {
		spin_unlock(&port_group_lock);
		kfree(pg);
		return tmp_pg;
	}

	list_add(&pg->node, &port_group_list);
	spin_unlock(&port_group_lock);

	return pg;
}