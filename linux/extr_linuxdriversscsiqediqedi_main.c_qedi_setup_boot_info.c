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
struct qedi_ctx {int /*<<< orphan*/  boot_kset; TYPE_1__* shost; } ;
struct iscsi_boot_kobj {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  host_no; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EPERM ; 
 struct iscsi_boot_kobj* iscsi_boot_create_ethernet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct qedi_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsi_boot_create_host_kset (int /*<<< orphan*/ ) ; 
 struct iscsi_boot_kobj* iscsi_boot_create_initiator (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct qedi_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct iscsi_boot_kobj* iscsi_boot_create_target (int /*<<< orphan*/ ,int,struct qedi_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsi_boot_destroy_kset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qedi_boot_release ; 
 int /*<<< orphan*/  qedi_eth_get_attr_visibility ; 
 scalar_t__ qedi_get_boot_info (struct qedi_ctx*) ; 
 int /*<<< orphan*/  qedi_ini_get_attr_visibility ; 
 int /*<<< orphan*/  qedi_show_boot_eth_info ; 
 int /*<<< orphan*/  qedi_show_boot_ini_info ; 
 int /*<<< orphan*/  qedi_show_boot_tgt_pri_info ; 
 int /*<<< orphan*/  qedi_show_boot_tgt_sec_info ; 
 int /*<<< orphan*/  qedi_tgt_get_attr_visibility ; 
 int /*<<< orphan*/  scsi_host_get (TYPE_1__*) ; 
 int /*<<< orphan*/  scsi_host_put (TYPE_1__*) ; 

__attribute__((used)) static int qedi_setup_boot_info(struct qedi_ctx *qedi)
{
	struct iscsi_boot_kobj *boot_kobj;

	if (qedi_get_boot_info(qedi))
		return -EPERM;

	qedi->boot_kset = iscsi_boot_create_host_kset(qedi->shost->host_no);
	if (!qedi->boot_kset)
		goto kset_free;

	if (!scsi_host_get(qedi->shost))
		goto kset_free;

	boot_kobj = iscsi_boot_create_target(qedi->boot_kset, 0, qedi,
					     qedi_show_boot_tgt_pri_info,
					     qedi_tgt_get_attr_visibility,
					     qedi_boot_release);
	if (!boot_kobj)
		goto put_host;

	if (!scsi_host_get(qedi->shost))
		goto kset_free;

	boot_kobj = iscsi_boot_create_target(qedi->boot_kset, 1, qedi,
					     qedi_show_boot_tgt_sec_info,
					     qedi_tgt_get_attr_visibility,
					     qedi_boot_release);
	if (!boot_kobj)
		goto put_host;

	if (!scsi_host_get(qedi->shost))
		goto kset_free;

	boot_kobj = iscsi_boot_create_initiator(qedi->boot_kset, 0, qedi,
						qedi_show_boot_ini_info,
						qedi_ini_get_attr_visibility,
						qedi_boot_release);
	if (!boot_kobj)
		goto put_host;

	if (!scsi_host_get(qedi->shost))
		goto kset_free;

	boot_kobj = iscsi_boot_create_ethernet(qedi->boot_kset, 0, qedi,
					       qedi_show_boot_eth_info,
					       qedi_eth_get_attr_visibility,
					       qedi_boot_release);
	if (!boot_kobj)
		goto put_host;

	return 0;

put_host:
	scsi_host_put(qedi->shost);
kset_free:
	iscsi_boot_destroy_kset(qedi->boot_kset);
	return -ENOMEM;
}