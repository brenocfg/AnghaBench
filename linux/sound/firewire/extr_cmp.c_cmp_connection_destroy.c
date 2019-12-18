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
struct cmp_connection {int /*<<< orphan*/  resources; int /*<<< orphan*/  mutex; int /*<<< orphan*/  connected; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fw_iso_resources_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 

void cmp_connection_destroy(struct cmp_connection *c)
{
	WARN_ON(c->connected);
	mutex_destroy(&c->mutex);
	fw_iso_resources_destroy(&c->resources);
}