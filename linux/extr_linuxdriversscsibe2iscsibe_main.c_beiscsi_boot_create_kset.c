#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct iscsi_boot_kobj {int dummy; } ;
struct boot_struct {int /*<<< orphan*/ * boot_kset; } ;
struct beiscsi_hba {TYPE_1__* shost; struct boot_struct boot_struct; } ;
struct TYPE_3__ {int /*<<< orphan*/  host_no; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  __beiscsi_log (struct beiscsi_hba*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  beiscsi_boot_kobj_release ; 
 int /*<<< orphan*/  beiscsi_eth_get_attr_visibility ; 
 int /*<<< orphan*/  beiscsi_ini_get_attr_visibility ; 
 int /*<<< orphan*/  beiscsi_show_boot_eth_info ; 
 int /*<<< orphan*/  beiscsi_show_boot_ini_info ; 
 int /*<<< orphan*/  beiscsi_show_boot_tgt_info ; 
 int /*<<< orphan*/  beiscsi_tgt_get_attr_visibility ; 
 struct iscsi_boot_kobj* iscsi_boot_create_ethernet (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct beiscsi_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * iscsi_boot_create_host_kset (int /*<<< orphan*/ ) ; 
 struct iscsi_boot_kobj* iscsi_boot_create_initiator (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct beiscsi_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct iscsi_boot_kobj* iscsi_boot_create_target (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct beiscsi_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsi_boot_destroy_kset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_host_get (TYPE_1__*) ; 
 int /*<<< orphan*/  scsi_host_put (TYPE_1__*) ; 

__attribute__((used)) static int beiscsi_boot_create_kset(struct beiscsi_hba *phba)
{
	struct boot_struct *bs = &phba->boot_struct;
	struct iscsi_boot_kobj *boot_kobj;

	if (bs->boot_kset) {
		__beiscsi_log(phba, KERN_ERR,
			      "BM_%d: boot_kset already created\n");
		return 0;
	}

	bs->boot_kset = iscsi_boot_create_host_kset(phba->shost->host_no);
	if (!bs->boot_kset) {
		__beiscsi_log(phba, KERN_ERR,
			      "BM_%d: boot_kset alloc failed\n");
		return -ENOMEM;
	}

	/* get shost ref because the show function will refer phba */
	if (!scsi_host_get(phba->shost))
		goto free_kset;

	boot_kobj = iscsi_boot_create_target(bs->boot_kset, 0, phba,
					     beiscsi_show_boot_tgt_info,
					     beiscsi_tgt_get_attr_visibility,
					     beiscsi_boot_kobj_release);
	if (!boot_kobj)
		goto put_shost;

	if (!scsi_host_get(phba->shost))
		goto free_kset;

	boot_kobj = iscsi_boot_create_initiator(bs->boot_kset, 0, phba,
						beiscsi_show_boot_ini_info,
						beiscsi_ini_get_attr_visibility,
						beiscsi_boot_kobj_release);
	if (!boot_kobj)
		goto put_shost;

	if (!scsi_host_get(phba->shost))
		goto free_kset;

	boot_kobj = iscsi_boot_create_ethernet(bs->boot_kset, 0, phba,
					       beiscsi_show_boot_eth_info,
					       beiscsi_eth_get_attr_visibility,
					       beiscsi_boot_kobj_release);
	if (!boot_kobj)
		goto put_shost;

	return 0;

put_shost:
	scsi_host_put(phba->shost);
free_kset:
	iscsi_boot_destroy_kset(bs->boot_kset);
	bs->boot_kset = NULL;
	return -ENOMEM;
}