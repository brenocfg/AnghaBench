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
struct gb_cap {int /*<<< orphan*/  node; int /*<<< orphan*/  cdev; int /*<<< orphan*/  class_device; int /*<<< orphan*/  dev_num; int /*<<< orphan*/ * parent; int /*<<< orphan*/  kref; int /*<<< orphan*/  mutex; struct gb_connection* connection; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NUM_MINORS ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cap_class ; 
 int /*<<< orphan*/  cap_dev_num ; 
 int /*<<< orphan*/  cap_fops ; 
 int /*<<< orphan*/  cap_list ; 
 int /*<<< orphan*/  cap_minors_map ; 
 int cdev_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cdev_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cdev_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  gb_connection_disable (struct gb_connection*) ; 
 int gb_connection_enable (struct gb_connection*) ; 
 int /*<<< orphan*/  gb_connection_set_data (struct gb_connection*,struct gb_cap*) ; 
 int ida_simple_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct gb_cap* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_mutex ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_cap (struct gb_cap*) ; 

int gb_cap_connection_init(struct gb_connection *connection)
{
	struct gb_cap *cap;
	int ret, minor;

	if (!connection)
		return 0;

	cap = kzalloc(sizeof(*cap), GFP_KERNEL);
	if (!cap)
		return -ENOMEM;

	cap->parent = &connection->bundle->dev;
	cap->connection = connection;
	mutex_init(&cap->mutex);
	gb_connection_set_data(connection, cap);
	kref_init(&cap->kref);

	mutex_lock(&list_mutex);
	list_add(&cap->node, &cap_list);
	mutex_unlock(&list_mutex);

	ret = gb_connection_enable(connection);
	if (ret)
		goto err_list_del;

	minor = ida_simple_get(&cap_minors_map, 0, NUM_MINORS, GFP_KERNEL);
	if (minor < 0) {
		ret = minor;
		goto err_connection_disable;
	}

	/* Add a char device to allow userspace to interact with cap */
	cap->dev_num = MKDEV(MAJOR(cap_dev_num), minor);
	cdev_init(&cap->cdev, &cap_fops);

	ret = cdev_add(&cap->cdev, cap->dev_num, 1);
	if (ret)
		goto err_remove_ida;

	/* Add a soft link to the previously added char-dev within the bundle */
	cap->class_device = device_create(cap_class, cap->parent, cap->dev_num,
					  NULL, "gb-authenticate-%d", minor);
	if (IS_ERR(cap->class_device)) {
		ret = PTR_ERR(cap->class_device);
		goto err_del_cdev;
	}

	return 0;

err_del_cdev:
	cdev_del(&cap->cdev);
err_remove_ida:
	ida_simple_remove(&cap_minors_map, minor);
err_connection_disable:
	gb_connection_disable(connection);
err_list_del:
	mutex_lock(&list_mutex);
	list_del(&cap->node);
	mutex_unlock(&list_mutex);

	put_cap(cap);

	return ret;
}