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
struct gbphy_device_id {int dummy; } ;
struct gbphy_device {int /*<<< orphan*/  dev; TYPE_1__* cport_desc; int /*<<< orphan*/  bundle; } ;
struct gb_connection {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct gb_connection*) ; 
 int PTR_ERR (struct gb_connection*) ; 
 struct gb_connection* gb_connection_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gb_connection_destroy (struct gb_connection*) ; 
 int /*<<< orphan*/  gb_connection_disable (struct gb_connection*) ; 
 int gb_connection_enable (struct gb_connection*) ; 
 int /*<<< orphan*/  gb_gbphy_set_data (struct gbphy_device*,struct gb_connection*) ; 
 int gb_spilib_master_init (struct gb_connection*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gbphy_runtime_put_autosuspend (struct gbphy_device*) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spilib_ops ; 

__attribute__((used)) static int gb_spi_probe(struct gbphy_device *gbphy_dev,
			const struct gbphy_device_id *id)
{
	struct gb_connection *connection;
	int ret;

	connection = gb_connection_create(gbphy_dev->bundle,
					  le16_to_cpu(gbphy_dev->cport_desc->id),
					  NULL);
	if (IS_ERR(connection))
		return PTR_ERR(connection);

	ret = gb_connection_enable(connection);
	if (ret)
		goto exit_connection_destroy;

	ret = gb_spilib_master_init(connection, &gbphy_dev->dev, spilib_ops);
	if (ret)
		goto exit_connection_disable;

	gb_gbphy_set_data(gbphy_dev, connection);

	gbphy_runtime_put_autosuspend(gbphy_dev);
	return 0;

exit_connection_disable:
	gb_connection_disable(connection);
exit_connection_destroy:
	gb_connection_destroy(connection);

	return ret;
}