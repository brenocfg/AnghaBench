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
struct config_group {int dummy; } ;
struct dlm_space {struct config_group group; scalar_t__ members_count; int /*<<< orphan*/  members_lock; int /*<<< orphan*/  members; struct config_group ns_group; } ;
struct dlm_nodes {struct config_group group; scalar_t__ members_count; int /*<<< orphan*/  members_lock; int /*<<< orphan*/  members; struct config_group ns_group; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct config_group* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  config_group_init_type_name (struct config_group*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  configfs_add_default_group (struct config_group*,struct config_group*) ; 
 int /*<<< orphan*/  kfree (struct dlm_space*) ; 
 struct dlm_space* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nodes_type ; 
 int /*<<< orphan*/  space_type ; 

__attribute__((used)) static struct config_group *make_space(struct config_group *g, const char *name)
{
	struct dlm_space *sp = NULL;
	struct dlm_nodes *nds = NULL;

	sp = kzalloc(sizeof(struct dlm_space), GFP_NOFS);
	nds = kzalloc(sizeof(struct dlm_nodes), GFP_NOFS);

	if (!sp || !nds)
		goto fail;

	config_group_init_type_name(&sp->group, name, &space_type);

	config_group_init_type_name(&nds->ns_group, "nodes", &nodes_type);
	configfs_add_default_group(&nds->ns_group, &sp->group);

	INIT_LIST_HEAD(&sp->members);
	mutex_init(&sp->members_lock);
	sp->members_count = 0;
	return &sp->group;

 fail:
	kfree(sp);
	kfree(nds);
	return ERR_PTR(-ENOMEM);
}