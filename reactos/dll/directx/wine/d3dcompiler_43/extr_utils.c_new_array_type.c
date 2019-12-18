#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned int elements_count; struct hlsl_type* type; } ;
struct TYPE_4__ {TYPE_1__ array; } ;
struct hlsl_type {TYPE_2__ e; int /*<<< orphan*/  modifiers; } ;

/* Variables and functions */
 int /*<<< orphan*/  HLSL_CLASS_ARRAY ; 
 int /*<<< orphan*/  HLSL_TYPE_FLOAT ; 
 struct hlsl_type* new_hlsl_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

struct hlsl_type *new_array_type(struct hlsl_type *basic_type, unsigned int array_size)
{
    struct hlsl_type *type = new_hlsl_type(NULL, HLSL_CLASS_ARRAY, HLSL_TYPE_FLOAT, 1, 1);

    if (!type)
        return NULL;

    type->modifiers = basic_type->modifiers;
    type->e.array.elements_count = array_size;
    type->e.array.type = basic_type;
    return type;
}