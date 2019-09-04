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
struct gb_channel {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct gb_connection* get_conn_from_channel (struct gb_channel*) ; 

__attribute__((used)) static int gb_lights_channel_flash_config(struct gb_channel *channel)
{
	struct gb_connection *connection = get_conn_from_channel(channel);

	dev_err(&connection->bundle->dev, "no support for flash devices\n");
	return 0;
}