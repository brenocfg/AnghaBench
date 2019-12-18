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
struct symt {int dummy; } ;
struct TYPE_2__ {unsigned int num_defined_types; struct symt** defined_types; } ;

/* Variables and functions */
 int FALSE ; 
 unsigned int FIRST_DEFINABLE_TYPE ; 
 int /*<<< orphan*/  FIXME (char*,...) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 struct symt** HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct symt** HeapReAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct symt**,int) ; 
 int TRUE ; 
 TYPE_1__* cv_current_module ; 
 void* max (int,unsigned int) ; 

__attribute__((used)) static int codeview_add_type(unsigned int typeno, struct symt* dt)
{
    if (typeno < FIRST_DEFINABLE_TYPE)
        FIXME("What the heck\n");
    if (!cv_current_module)
    {
        FIXME("Adding %x to non allowed module\n", typeno);
        return FALSE;
    }
    if ((typeno >> 24) != 0)
        FIXME("No module index while inserting type-id assumption is wrong %x\n",
              typeno);
    if (typeno - FIRST_DEFINABLE_TYPE >= cv_current_module->num_defined_types)
    {
        if (cv_current_module->defined_types)
        {
            cv_current_module->num_defined_types = max( cv_current_module->num_defined_types * 2,
                                                        typeno - FIRST_DEFINABLE_TYPE + 1 );
            cv_current_module->defined_types = HeapReAlloc(GetProcessHeap(),
                            HEAP_ZERO_MEMORY, cv_current_module->defined_types,
                            cv_current_module->num_defined_types * sizeof(struct symt*));
        }
        else
        {
            cv_current_module->num_defined_types = max( 256, typeno - FIRST_DEFINABLE_TYPE + 1 );
            cv_current_module->defined_types = HeapAlloc(GetProcessHeap(),
                            HEAP_ZERO_MEMORY,
                            cv_current_module->num_defined_types * sizeof(struct symt*));
        }
        if (cv_current_module->defined_types == NULL) return FALSE;
    }
    if (cv_current_module->defined_types[typeno - FIRST_DEFINABLE_TYPE])
    {
        if (cv_current_module->defined_types[typeno - FIRST_DEFINABLE_TYPE] != dt)
            FIXME("Overwriting at %x\n", typeno);
    }
    cv_current_module->defined_types[typeno - FIRST_DEFINABLE_TYPE] = dt;
    return TRUE;
}