#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  children; } ;
typedef  TYPE_1__ obs_hotkey_name_map_node_t ;
struct TYPE_13__ {scalar_t__ prefix_len; TYPE_1__* node; } ;
typedef  TYPE_2__ obs_hotkey_name_map_edge_t ;

/* Variables and functions */
 int /*<<< orphan*/  add_leaf (TYPE_1__*,char const*,size_t,int) ; 
 int /*<<< orphan*/  connect (TYPE_2__*,TYPE_1__*) ; 
 TYPE_2__* da_push_back_new (int /*<<< orphan*/ ) ; 
 char* get_prefix (TYPE_2__*) ; 
 TYPE_1__* new_node () ; 
 int /*<<< orphan*/  set_prefix (TYPE_2__*,char const*,scalar_t__) ; 
 int /*<<< orphan*/  shrink_prefix (TYPE_2__*,size_t) ; 

__attribute__((used)) static void reduce_edge(obs_hotkey_name_map_edge_t *e, const char *key,
			size_t l, int v)
{
	const char *str = get_prefix(e), *str_ = key;
	size_t common_length = 0;
	while (*str == *str_) {
		common_length += 1;
		str += 1;
		str_ += 1;
	}

	obs_hotkey_name_map_node_t *new_node_ = new_node();
	obs_hotkey_name_map_edge_t *tail =
		da_push_back_new(new_node_->children);

	connect(tail, e->node);
	set_prefix(tail, str, e->prefix_len - common_length);

	add_leaf(new_node_, str_, l - common_length, v);

	connect(e, new_node_);
	shrink_prefix(e, common_length);
}