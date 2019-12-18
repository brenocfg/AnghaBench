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

/* Variables and functions */
 unsigned int ARRAY_SIZE (scalar_t__*) ; 
 int /*<<< orphan*/  ITypeInfo_Release (scalar_t__) ; 
 int /*<<< orphan*/  ITypeLib_Release (scalar_t__) ; 
 scalar_t__* typeinfo ; 
 scalar_t__ typelib ; 

void release_typelib(void)
{
    unsigned i;

    for (i = 0; i < ARRAY_SIZE(typeinfo); i++)
        if (typeinfo[i])
            ITypeInfo_Release(typeinfo[i]);

    if (typelib)
        ITypeLib_Release(typelib);
}