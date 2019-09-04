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
typedef  scalar_t__ uint32_t ;
struct iscsi_transport {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  parent; int /*<<< orphan*/  kobj; int /*<<< orphan*/ * class; int /*<<< orphan*/  release; } ;
struct iscsi_iface {TYPE_1__ dev; struct iscsi_iface* dd_data; scalar_t__ iface_num; scalar_t__ iface_type; struct iscsi_transport* transport; } ;
struct Scsi_Host {int /*<<< orphan*/  host_no; int /*<<< orphan*/  shost_gendev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ ISCSI_IFACE_TYPE_IPV4 ; 
 int /*<<< orphan*/  dev_set_name (TYPE_1__*,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int device_register (TYPE_1__*) ; 
 int /*<<< orphan*/  device_unregister (TYPE_1__*) ; 
 int /*<<< orphan*/  get_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iscsi_iface_class ; 
 int /*<<< orphan*/  iscsi_iface_group ; 
 int /*<<< orphan*/  iscsi_iface_release ; 
 int /*<<< orphan*/  kfree (struct iscsi_iface*) ; 
 struct iscsi_iface* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ ) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

struct iscsi_iface *
iscsi_create_iface(struct Scsi_Host *shost, struct iscsi_transport *transport,
		   uint32_t iface_type, uint32_t iface_num, int dd_size)
{
	struct iscsi_iface *iface;
	int err;

	iface = kzalloc(sizeof(*iface) + dd_size, GFP_KERNEL);
	if (!iface)
		return NULL;

	iface->transport = transport;
	iface->iface_type = iface_type;
	iface->iface_num = iface_num;
	iface->dev.release = iscsi_iface_release;
	iface->dev.class = &iscsi_iface_class;
	/* parent reference released in iscsi_iface_release */
	iface->dev.parent = get_device(&shost->shost_gendev);
	if (iface_type == ISCSI_IFACE_TYPE_IPV4)
		dev_set_name(&iface->dev, "ipv4-iface-%u-%u", shost->host_no,
			     iface_num);
	else
		dev_set_name(&iface->dev, "ipv6-iface-%u-%u", shost->host_no,
			     iface_num);

	err = device_register(&iface->dev);
	if (err)
		goto free_iface;

	err = sysfs_create_group(&iface->dev.kobj, &iscsi_iface_group);
	if (err)
		goto unreg_iface;

	if (dd_size)
		iface->dd_data = &iface[1];
	return iface;

unreg_iface:
	device_unregister(&iface->dev);
	return NULL;

free_iface:
	put_device(iface->dev.parent);
	kfree(iface);
	return NULL;
}