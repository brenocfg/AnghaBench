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
struct greybus_descriptor_cport {scalar_t__ protocol_id; int /*<<< orphan*/  id; } ;
struct greybus_bundle_id {int dummy; } ;
struct gb_lights {struct gb_connection* connection; int /*<<< orphan*/  lights_lock; } ;
struct gb_connection {int dummy; } ;
struct gb_bundle {int num_cports; struct greybus_descriptor_cport* cport_desc; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ GREYBUS_PROTOCOL_LIGHTS ; 
 scalar_t__ IS_ERR (struct gb_connection*) ; 
 int PTR_ERR (struct gb_connection*) ; 
 struct gb_connection* gb_connection_create (struct gb_bundle*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gb_connection_destroy (struct gb_connection*) ; 
 int /*<<< orphan*/  gb_connection_disable (struct gb_connection*) ; 
 int gb_connection_enable (struct gb_connection*) ; 
 int gb_connection_enable_tx (struct gb_connection*) ; 
 int /*<<< orphan*/  gb_connection_set_data (struct gb_connection*,struct gb_lights*) ; 
 int gb_lights_create_all (struct gb_lights*) ; 
 int gb_lights_register_all (struct gb_lights*) ; 
 int /*<<< orphan*/  gb_lights_release (struct gb_lights*) ; 
 int /*<<< orphan*/  gb_lights_request_handler ; 
 int /*<<< orphan*/  gb_pm_runtime_put_autosuspend (struct gb_bundle*) ; 
 int /*<<< orphan*/  greybus_set_drvdata (struct gb_bundle*,struct gb_lights*) ; 
 struct gb_lights* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gb_lights_probe(struct gb_bundle *bundle,
			   const struct greybus_bundle_id *id)
{
	struct greybus_descriptor_cport *cport_desc;
	struct gb_connection *connection;
	struct gb_lights *glights;
	int ret;

	if (bundle->num_cports != 1)
		return -ENODEV;

	cport_desc = &bundle->cport_desc[0];
	if (cport_desc->protocol_id != GREYBUS_PROTOCOL_LIGHTS)
		return -ENODEV;

	glights = kzalloc(sizeof(*glights), GFP_KERNEL);
	if (!glights)
		return -ENOMEM;

	mutex_init(&glights->lights_lock);

	connection = gb_connection_create(bundle, le16_to_cpu(cport_desc->id),
					  gb_lights_request_handler);
	if (IS_ERR(connection)) {
		ret = PTR_ERR(connection);
		goto out;
	}

	glights->connection = connection;
	gb_connection_set_data(connection, glights);

	greybus_set_drvdata(bundle, glights);

	/* We aren't ready to receive an incoming request yet */
	ret = gb_connection_enable_tx(connection);
	if (ret)
		goto error_connection_destroy;

	/*
	 * Setup all the lights devices over this connection, if anything goes
	 * wrong tear down all lights
	 */
	ret = gb_lights_create_all(glights);
	if (ret < 0)
		goto error_connection_disable;

	/* We are ready to receive an incoming request now, enable RX as well */
	ret = gb_connection_enable(connection);
	if (ret)
		goto error_connection_disable;

	/* Enable & register lights */
	ret = gb_lights_register_all(glights);
	if (ret < 0)
		goto error_connection_disable;

	gb_pm_runtime_put_autosuspend(bundle);

	return 0;

error_connection_disable:
	gb_connection_disable(connection);
error_connection_destroy:
	gb_connection_destroy(connection);
out:
	gb_lights_release(glights);
	return ret;
}