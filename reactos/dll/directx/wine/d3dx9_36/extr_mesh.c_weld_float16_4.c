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
typedef  scalar_t__ FLOAT ;
typedef  int /*<<< orphan*/  D3DXFLOAT16 ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  D3DXFloat16To32Array (scalar_t__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  FALSE ; 
 int NUM_ELEM ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ fabsf (scalar_t__) ; 
 scalar_t__ max (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 

__attribute__((used)) static BOOL weld_float16_4(void *to, void *from, FLOAT epsilon)
{
    D3DXFLOAT16 *v1_float16 = to;
    D3DXFLOAT16 *v2_float16 = from;
    FLOAT diff_x;
    FLOAT diff_y;
    FLOAT diff_z;
    FLOAT diff_w;
    FLOAT max_abs_diff;
#define NUM_ELEM 4
    FLOAT v1[NUM_ELEM];
    FLOAT v2[NUM_ELEM];

    D3DXFloat16To32Array(v1, v1_float16, NUM_ELEM);
    D3DXFloat16To32Array(v2, v2_float16, NUM_ELEM);

    diff_x = fabsf(v1[0] - v2[0]);
    diff_y = fabsf(v1[1] - v2[1]);
    diff_z = fabsf(v1[2] - v2[2]);
    diff_w = fabsf(v1[3] - v2[3]);
    max_abs_diff = max(diff_x, diff_y);
    max_abs_diff = max(diff_z, max_abs_diff);
    max_abs_diff = max(diff_w, max_abs_diff);

    if (max_abs_diff <= epsilon)
    {
        memcpy(to, from, NUM_ELEM * sizeof(D3DXFLOAT16));

        return TRUE;
    }

    return FALSE;
#undef NUM_ELEM
}