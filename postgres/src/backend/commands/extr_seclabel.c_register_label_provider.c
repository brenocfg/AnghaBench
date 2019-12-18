#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  check_object_relabel_type ;
struct TYPE_4__ {int /*<<< orphan*/  hook; int /*<<< orphan*/  provider_name; } ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_1__ LabelProvider ;

/* Variables and functions */
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TopMemoryContext ; 
 int /*<<< orphan*/  label_provider_list ; 
 int /*<<< orphan*/  lappend (int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_1__* palloc (int) ; 
 int /*<<< orphan*/  pstrdup (char const*) ; 

void
register_label_provider(const char *provider_name, check_object_relabel_type hook)
{
	LabelProvider *provider;
	MemoryContext oldcxt;

	oldcxt = MemoryContextSwitchTo(TopMemoryContext);
	provider = palloc(sizeof(LabelProvider));
	provider->provider_name = pstrdup(provider_name);
	provider->hook = hook;
	label_provider_list = lappend(label_provider_list, provider);
	MemoryContextSwitchTo(oldcxt);
}