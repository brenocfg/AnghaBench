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
struct fw_download {int /*<<< orphan*/  id_map; int /*<<< orphan*/  mutex; struct gb_connection* connection; int /*<<< orphan*/  fw_requests; int /*<<< orphan*/ * parent; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int gb_connection_enable (struct gb_connection*) ; 
 int /*<<< orphan*/  gb_connection_set_data (struct gb_connection*,struct fw_download*) ; 
 int /*<<< orphan*/  ida_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ida_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct fw_download*) ; 
 struct fw_download* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

int gb_fw_download_connection_init(struct gb_connection *connection)
{
	struct fw_download *fw_download;
	int ret;

	if (!connection)
		return 0;

	fw_download = kzalloc(sizeof(*fw_download), GFP_KERNEL);
	if (!fw_download)
		return -ENOMEM;

	fw_download->parent = &connection->bundle->dev;
	INIT_LIST_HEAD(&fw_download->fw_requests);
	ida_init(&fw_download->id_map);
	gb_connection_set_data(connection, fw_download);
	fw_download->connection = connection;
	mutex_init(&fw_download->mutex);

	ret = gb_connection_enable(connection);
	if (ret)
		goto err_destroy_id_map;

	return 0;

err_destroy_id_map:
	ida_destroy(&fw_download->id_map);
	kfree(fw_download);

	return ret;
}