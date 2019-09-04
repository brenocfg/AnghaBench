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
typedef  enum hlsl_base_type { ____Placeholder_hlsl_base_type } hlsl_base_type ;

/* Variables and functions */
 int ARRAY_SIZE (int const*) ; 
 int /*<<< orphan*/  FIXME (char*) ; 
#define  HLSL_TYPE_BOOL 133 
#define  HLSL_TYPE_DOUBLE 132 
#define  HLSL_TYPE_FLOAT 131 
#define  HLSL_TYPE_HALF 130 
#define  HLSL_TYPE_INT 129 
#define  HLSL_TYPE_UINT 128 

__attribute__((used)) static enum hlsl_base_type expr_common_base_type(enum hlsl_base_type t1, enum hlsl_base_type t2)
{
    static const enum hlsl_base_type types[] =
    {
        HLSL_TYPE_BOOL,
        HLSL_TYPE_INT,
        HLSL_TYPE_UINT,
        HLSL_TYPE_HALF,
        HLSL_TYPE_FLOAT,
        HLSL_TYPE_DOUBLE,
    };
    int t1_idx = -1, t2_idx = -1, i;

    for (i = 0; i < ARRAY_SIZE(types); ++i)
    {
        /* Always convert away from HLSL_TYPE_HALF */
        if (t1 == types[i])
            t1_idx = t1 == HLSL_TYPE_HALF ? i + 1 : i;
        if (t2 == types[i])
            t2_idx = t2 == HLSL_TYPE_HALF ? i + 1 : i;

        if (t1_idx != -1 && t2_idx != -1)
            break;
    }
    if (t1_idx == -1 || t2_idx == -1)
    {
        FIXME("Unexpected base type.\n");
        return HLSL_TYPE_FLOAT;
    }
    return t1_idx >= t2_idx ? t1 : t2;
}