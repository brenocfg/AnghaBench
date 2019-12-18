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
struct TYPE_3__ {int /*<<< orphan*/  type; } ;
struct TYPE_4__ {TYPE_1__ array; } ;
struct hlsl_type {scalar_t__ type; int dimx; int dimy; TYPE_2__ e; } ;
typedef  int BOOL ;

/* Variables and functions */
 int FALSE ; 
 scalar_t__ HLSL_CLASS_ARRAY ; 
 scalar_t__ HLSL_CLASS_LAST_NUMERIC ; 
 scalar_t__ HLSL_CLASS_MATRIX ; 
 scalar_t__ HLSL_CLASS_STRUCT ; 
 scalar_t__ HLSL_CLASS_VECTOR ; 
 int TRUE ; 
 scalar_t__ compare_hlsl_types (int /*<<< orphan*/ ,struct hlsl_type*) ; 
 scalar_t__ components_count_type (struct hlsl_type*) ; 
 int /*<<< orphan*/  convertible_data_type (struct hlsl_type*) ; 

BOOL compatible_data_types(struct hlsl_type *t1, struct hlsl_type *t2)
{
   if (!convertible_data_type(t1) || !convertible_data_type(t2))
        return FALSE;

    if (t1->type <= HLSL_CLASS_LAST_NUMERIC)
    {
        /* Scalar vars can be cast to pretty much everything */
        if (t1->dimx == 1 && t1->dimy == 1)
            return TRUE;

        if (t1->type == HLSL_CLASS_VECTOR && t2->type == HLSL_CLASS_VECTOR)
            return t1->dimx >= t2->dimx;
    }

    /* The other way around is true too i.e. whatever to scalar */
    if (t2->type <= HLSL_CLASS_LAST_NUMERIC && t2->dimx == 1 && t2->dimy == 1)
        return TRUE;

    if (t1->type == HLSL_CLASS_ARRAY)
    {
        if (compare_hlsl_types(t1->e.array.type, t2))
            /* e.g. float4[3] to float4 is allowed */
            return TRUE;

        if (t2->type == HLSL_CLASS_ARRAY || t2->type == HLSL_CLASS_STRUCT)
            return components_count_type(t1) >= components_count_type(t2);
        else
            return components_count_type(t1) == components_count_type(t2);
    }

    if (t1->type == HLSL_CLASS_STRUCT)
        return components_count_type(t1) >= components_count_type(t2);

    if (t2->type == HLSL_CLASS_ARRAY || t2->type == HLSL_CLASS_STRUCT)
        return components_count_type(t1) == components_count_type(t2);

    if (t1->type == HLSL_CLASS_MATRIX || t2->type == HLSL_CLASS_MATRIX)
    {
        if (t1->type == HLSL_CLASS_MATRIX && t2->type == HLSL_CLASS_MATRIX && t1->dimx >= t2->dimx && t1->dimy >= t2->dimy)
            return TRUE;

        /* Matrix-vector conversion is apparently allowed if they have the same components count */
        if ((t1->type == HLSL_CLASS_VECTOR || t2->type == HLSL_CLASS_VECTOR)
                && components_count_type(t1) == components_count_type(t2))
            return TRUE;
        return FALSE;
    }

    if (components_count_type(t1) >= components_count_type(t2))
        return TRUE;
    return FALSE;
}