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
 int /*<<< orphan*/  ITypeLib_Release (int /*<<< orphan*/ ) ; 
 scalar_t__* typeinfos ; 
 int /*<<< orphan*/  typelib ; 

__attribute__((used)) static void release_typelib(void)
{
    unsigned i;

    if(!typelib)
        return;

    for(i=0; i < ARRAY_SIZE(typeinfos); i++) {
        if(typeinfos[i])
            ITypeInfo_Release(typeinfos[i]);
    }

    ITypeLib_Release(typelib);
}