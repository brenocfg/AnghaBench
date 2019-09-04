#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  activate_refs; int /*<<< orphan*/  show_refs; } ;
typedef  TYPE_1__ obs_source_t ;
typedef  enum view_type { ____Placeholder_view_type } view_type ;

/* Variables and functions */
 int MAIN_VIEW ; 
 int /*<<< orphan*/  activate_tree ; 
 int /*<<< orphan*/  obs_source_enum_active_tree (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_source_valid (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  os_atomic_inc_long (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  show_tree ; 

void obs_source_activate(obs_source_t *source, enum view_type type)
{
	if (!obs_source_valid(source, "obs_source_activate"))
		return;

	os_atomic_inc_long(&source->show_refs);
	obs_source_enum_active_tree(source, show_tree, NULL);

	if (type == MAIN_VIEW) {
		os_atomic_inc_long(&source->activate_refs);
		obs_source_enum_active_tree(source, activate_tree, NULL);
	}
}