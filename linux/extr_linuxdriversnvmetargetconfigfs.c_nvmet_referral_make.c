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
struct nvmet_port {struct config_group group; int /*<<< orphan*/  entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct config_group* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  config_group_init_type_name (struct config_group*,char const*,int /*<<< orphan*/ *) ; 
 struct nvmet_port* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvmet_referral_type ; 

__attribute__((used)) static struct config_group *nvmet_referral_make(
		struct config_group *group, const char *name)
{
	struct nvmet_port *port;

	port = kzalloc(sizeof(*port), GFP_KERNEL);
	if (!port)
		return ERR_PTR(-ENOMEM);

	INIT_LIST_HEAD(&port->entry);
	config_group_init_type_name(&port->group, name, &nvmet_referral_type);

	return &port->group;
}