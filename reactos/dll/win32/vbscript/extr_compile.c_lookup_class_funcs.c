#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned int func_cnt; TYPE_1__* funcs; } ;
typedef  TYPE_2__ class_desc_t ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_4__ {scalar_t__ name; } ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  strcmpiW (scalar_t__,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static BOOL lookup_class_funcs(class_desc_t *class_desc, const WCHAR *name)
{
    unsigned i;

    for(i=0; i < class_desc->func_cnt; i++) {
        if(class_desc->funcs[i].name && !strcmpiW(class_desc->funcs[i].name, name))
            return TRUE;
    }

    return FALSE;
}