#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct gb_connection {TYPE_1__* bundle; } ;
struct fw_mgmt {int /*<<< orphan*/  node; int /*<<< orphan*/  cdev; int /*<<< orphan*/  class_device; int /*<<< orphan*/  dev_num; int /*<<< orphan*/ * parent; int /*<<< orphan*/  kref; int /*<<< orphan*/  mutex; int /*<<< orphan*/  id_map; int /*<<< orphan*/  completion; struct gb_connection* connection; int /*<<< orphan*/  timeout_jiffies; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  FW_MGMT_TIMEOUT_MS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NUM_MINORS ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int cdev_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cdev_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cdev_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  fw_mgmt_class ; 
 int /*<<< orphan*/  fw_mgmt_dev_num ; 
 int /*<<< orphan*/  fw_mgmt_fops ; 
 int /*<<< orphan*/  fw_mgmt_list ; 
 int /*<<< orphan*/  fw_mgmt_minors_map ; 
 int /*<<< orphan*/  gb_connection_disable (struct gb_connection*) ; 
 int gb_connection_enable (struct gb_connection*) ; 
 int /*<<< orphan*/  gb_connection_set_data (struct gb_connection*,struct fw_mgmt*) ; 
 int /*<<< orphan*/  ida_init (int /*<<< orphan*/ *) ; 
 int ida_simple_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct fw_mgmt* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_mutex ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_fw_mgmt (struct fw_mgmt*) ; 

int gb_fw_mgmt_connection_init(struct gb_connection *connection)
{
	struct fw_mgmt *fw_mgmt;
	int ret, minor;

	if (!connection)
		return 0;

	fw_mgmt = kzalloc(sizeof(*fw_mgmt), GFP_KERNEL);
	if (!fw_mgmt)
		return -ENOMEM;

	fw_mgmt->parent = &connection->bundle->dev;
	fw_mgmt->timeout_jiffies = msecs_to_jiffies(FW_MGMT_TIMEOUT_MS);
	fw_mgmt->connection = connection;

	gb_connection_set_data(connection, fw_mgmt);
	init_completion(&fw_mgmt->completion);
	ida_init(&fw_mgmt->id_map);
	mutex_init(&fw_mgmt->mutex);
	kref_init(&fw_mgmt->kref);

	mutex_lock(&list_mutex);
	list_add(&fw_mgmt->node, &fw_mgmt_list);
	mutex_unlock(&list_mutex);

	ret = gb_connection_enable(connection);
	if (ret)
		goto err_list_del;

	minor = ida_simple_get(&fw_mgmt_minors_map, 0, NUM_MINORS, GFP_KERNEL);
	if (minor < 0) {
		ret = minor;
		goto err_connection_disable;
	}

	/* Add a char device to allow userspace to interact with fw-mgmt */
	fw_mgmt->dev_num = MKDEV(MAJOR(fw_mgmt_dev_num), minor);
	cdev_init(&fw_mgmt->cdev, &fw_mgmt_fops);

	ret = cdev_add(&fw_mgmt->cdev, fw_mgmt->dev_num, 1);
	if (ret)
		goto err_remove_ida;

	/* Add a soft link to the previously added char-dev within the bundle */
	fw_mgmt->class_device = device_create(fw_mgmt_class, fw_mgmt->parent,
					      fw_mgmt->dev_num, NULL,
					      "gb-fw-mgmt-%d", minor);
	if (IS_ERR(fw_mgmt->class_device)) {
		ret = PTR_ERR(fw_mgmt->class_device);
		goto err_del_cdev;
	}

	return 0;

err_del_cdev:
	cdev_del(&fw_mgmt->cdev);
err_remove_ida:
	ida_simple_remove(&fw_mgmt_minors_map, minor);
err_connection_disable:
	gb_connection_disable(connection);
err_list_del:
	mutex_lock(&list_mutex);
	list_del(&fw_mgmt->node);
	mutex_unlock(&list_mutex);

	put_fw_mgmt(fw_mgmt);

	return ret;
}