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
struct dsa_switch {TYPE_1__* ops; } ;
struct dsa_port {int index; struct dsa_switch* ds; } ;
typedef  int /*<<< orphan*/  dsa_fdb_dump_cb_t ;
struct TYPE_2__ {int (* port_fdb_dump ) (struct dsa_switch*,int,int /*<<< orphan*/ *,void*) ;} ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int stub1 (struct dsa_switch*,int,int /*<<< orphan*/ *,void*) ; 

int dsa_port_fdb_dump(struct dsa_port *dp, dsa_fdb_dump_cb_t *cb, void *data)
{
	struct dsa_switch *ds = dp->ds;
	int port = dp->index;

	if (!ds->ops->port_fdb_dump)
		return -EOPNOTSUPP;

	return ds->ops->port_fdb_dump(ds, port, cb, data);
}