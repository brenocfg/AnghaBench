#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct ceph_options {int num_mon; struct ceph_entity_addr* mon_addr; } ;
struct ceph_mon_client {TYPE_4__* monmap; TYPE_1__* client; } ;
struct ceph_entity_addr {scalar_t__ nonce; } ;
struct TYPE_9__ {int num_mon; TYPE_3__* mon_inst; } ;
struct TYPE_7__ {int /*<<< orphan*/  num; int /*<<< orphan*/  type; } ;
struct TYPE_8__ {TYPE_2__ name; struct ceph_entity_addr addr; } ;
struct TYPE_6__ {struct ceph_options* options; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEPH_ENTITY_TYPE_MON ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cpu_to_le64 (int) ; 
 TYPE_4__* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mon_inst ; 
 int /*<<< orphan*/  struct_size (TYPE_4__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int build_initial_monmap(struct ceph_mon_client *monc)
{
	struct ceph_options *opt = monc->client->options;
	struct ceph_entity_addr *mon_addr = opt->mon_addr;
	int num_mon = opt->num_mon;
	int i;

	/* build initial monmap */
	monc->monmap = kzalloc(struct_size(monc->monmap, mon_inst, num_mon),
			       GFP_KERNEL);
	if (!monc->monmap)
		return -ENOMEM;
	for (i = 0; i < num_mon; i++) {
		monc->monmap->mon_inst[i].addr = mon_addr[i];
		monc->monmap->mon_inst[i].addr.nonce = 0;
		monc->monmap->mon_inst[i].name.type =
			CEPH_ENTITY_TYPE_MON;
		monc->monmap->mon_inst[i].name.num = cpu_to_le64(i);
	}
	monc->monmap->num_mon = num_mon;
	return 0;
}