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
struct config_item {int dummy; } ;
struct dlm_comm {int nodeid; struct config_item item; scalar_t__ addr_count; scalar_t__ local; scalar_t__ seq; } ;
struct config_group {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct config_item* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  comm_type ; 
 int /*<<< orphan*/  config_item_init_type_name (struct config_item*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dlm_comm_count ; 
 struct dlm_comm* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct config_item *make_comm(struct config_group *g, const char *name)
{
	struct dlm_comm *cm;

	cm = kzalloc(sizeof(struct dlm_comm), GFP_NOFS);
	if (!cm)
		return ERR_PTR(-ENOMEM);

	config_item_init_type_name(&cm->item, name, &comm_type);

	cm->seq = dlm_comm_count++;
	if (!cm->seq)
		cm->seq = dlm_comm_count++;

	cm->nodeid = -1;
	cm->local = 0;
	cm->addr_count = 0;
	return &cm->item;
}