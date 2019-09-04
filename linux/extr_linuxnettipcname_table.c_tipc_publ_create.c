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
typedef  void* u32 ;
struct publication {int /*<<< orphan*/  all_publ; int /*<<< orphan*/  local_publ; int /*<<< orphan*/  binding_node; int /*<<< orphan*/  binding_sock; void* key; void* port; void* node; void* scope; void* upper; void* lower; void* type; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct publication* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct publication *tipc_publ_create(u32 type, u32 lower, u32 upper,
					    u32 scope, u32 node, u32 port,
					    u32 key)
{
	struct publication *publ = kzalloc(sizeof(*publ), GFP_ATOMIC);

	if (!publ)
		return NULL;

	publ->type = type;
	publ->lower = lower;
	publ->upper = upper;
	publ->scope = scope;
	publ->node = node;
	publ->port = port;
	publ->key = key;
	INIT_LIST_HEAD(&publ->binding_sock);
	INIT_LIST_HEAD(&publ->binding_node);
	INIT_LIST_HEAD(&publ->local_publ);
	INIT_LIST_HEAD(&publ->all_publ);
	return publ;
}