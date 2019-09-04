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
struct device_connection {int /*<<< orphan*/ * endpoint; } ;

/* Variables and functions */
 int /*<<< orphan*/  __typec_port_match ; 
 void* class_find_device (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  typec_class ; 

__attribute__((used)) static void *typec_port_match(struct device_connection *con, int ep, void *data)
{
	return class_find_device(typec_class, NULL, con->endpoint[ep],
				 __typec_port_match);
}