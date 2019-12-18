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
struct TYPE_2__ {int Elements; size_t StructMembers; } ;
struct ctab_constant {struct ctab_constant* constants; TYPE_1__ desc; } ;
typedef  size_t UINT ;
typedef  int /*<<< orphan*/  D3DXHANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  handle_from_constant (struct ctab_constant*) ; 

__attribute__((used)) static struct ctab_constant *is_valid_sub_constant(struct ctab_constant *parent, D3DXHANDLE handle)
{
    struct ctab_constant *c;
    UINT i, count;

    /* all variable have at least elements = 1, but not always elements */
    if (!parent->constants) return NULL;

    count = parent->desc.Elements > 1 ? parent->desc.Elements : parent->desc.StructMembers;
    for (i = 0; i < count; ++i)
    {
        if (handle_from_constant(&parent->constants[i]) == handle)
            return &parent->constants[i];

        c = is_valid_sub_constant(&parent->constants[i], handle);
        if (c) return c;
    }

    return NULL;
}