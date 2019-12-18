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
struct cmp_connection {int connected; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  SUCCEED_ON_BUS_RESET ; 
 int /*<<< orphan*/  cmp_error (struct cmp_connection*,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcr_break_modify ; 
 int pcr_modify (struct cmp_connection*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void cmp_connection_break(struct cmp_connection *c)
{
	int err;

	mutex_lock(&c->mutex);

	if (!c->connected) {
		mutex_unlock(&c->mutex);
		return;
	}

	err = pcr_modify(c, pcr_break_modify, NULL, SUCCEED_ON_BUS_RESET);
	if (err < 0)
		cmp_error(c, "plug is still connected\n");

	c->connected = false;

	mutex_unlock(&c->mutex);
}