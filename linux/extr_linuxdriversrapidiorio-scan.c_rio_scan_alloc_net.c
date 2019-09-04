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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int /*<<< orphan*/  release; int /*<<< orphan*/ * parent; } ;
struct rio_net {TYPE_1__ dev; int /*<<< orphan*/  id; struct rio_mport* hport; int /*<<< orphan*/  release; struct rio_id_table* enum_data; } ;
struct rio_mport {int /*<<< orphan*/  dev; int /*<<< orphan*/  id; int /*<<< orphan*/  sys_size; } ;
struct rio_id_table {int /*<<< orphan*/  lock; int /*<<< orphan*/  max; int /*<<< orphan*/  start; } ;

/* Variables and functions */
 int BITS_TO_LONGS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  RIO_MAX_ROUTE_ENTRIES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_set_name (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 struct rio_id_table* kzalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  rio_add_net (struct rio_net*) ; 
 struct rio_net* rio_alloc_net (struct rio_mport*) ; 
 int /*<<< orphan*/  rio_free_net (struct rio_net*) ; 
 int /*<<< orphan*/  rio_scan_release_dev ; 
 int /*<<< orphan*/  rio_scan_release_net ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct rio_net *rio_scan_alloc_net(struct rio_mport *mport,
					  int do_enum, u16 start)
{
	struct rio_net *net;

	net = rio_alloc_net(mport);

	if (net && do_enum) {
		struct rio_id_table *idtab;
		size_t size;

		size = sizeof(struct rio_id_table) +
				BITS_TO_LONGS(
					RIO_MAX_ROUTE_ENTRIES(mport->sys_size)
					) * sizeof(long);

		idtab = kzalloc(size, GFP_KERNEL);

		if (idtab == NULL) {
			pr_err("RIO: failed to allocate destID table\n");
			rio_free_net(net);
			net = NULL;
		} else {
			net->enum_data = idtab;
			net->release = rio_scan_release_net;
			idtab->start = start;
			idtab->max = RIO_MAX_ROUTE_ENTRIES(mport->sys_size);
			spin_lock_init(&idtab->lock);
		}
	}

	if (net) {
		net->id = mport->id;
		net->hport = mport;
		dev_set_name(&net->dev, "rnet_%d", net->id);
		net->dev.parent = &mport->dev;
		net->dev.release = rio_scan_release_dev;
		rio_add_net(net);
	}

	return net;
}