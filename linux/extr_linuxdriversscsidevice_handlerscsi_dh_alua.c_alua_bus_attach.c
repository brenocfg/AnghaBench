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
struct scsi_device {struct alua_dh_data* handler_data; } ;
struct alua_dh_data {int init_error; int /*<<< orphan*/  init_mutex; int /*<<< orphan*/  node; struct scsi_device* sdev; int /*<<< orphan*/  pg; int /*<<< orphan*/  pg_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int SCSI_DH_DEV_OFFLINED ; 
 int SCSI_DH_NOMEM ; 
 int SCSI_DH_OK ; 
 int alua_initialize (struct scsi_device*,struct alua_dh_data*) ; 
 int /*<<< orphan*/  kfree (struct alua_dh_data*) ; 
 struct alua_dh_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int alua_bus_attach(struct scsi_device *sdev)
{
	struct alua_dh_data *h;
	int err;

	h = kzalloc(sizeof(*h) , GFP_KERNEL);
	if (!h)
		return SCSI_DH_NOMEM;
	spin_lock_init(&h->pg_lock);
	rcu_assign_pointer(h->pg, NULL);
	h->init_error = SCSI_DH_OK;
	h->sdev = sdev;
	INIT_LIST_HEAD(&h->node);

	mutex_init(&h->init_mutex);
	err = alua_initialize(sdev, h);
	if (err != SCSI_DH_OK && err != SCSI_DH_DEV_OFFLINED)
		goto failed;

	sdev->handler_data = h;
	return SCSI_DH_OK;
failed:
	kfree(h);
	return err;
}