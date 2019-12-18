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
struct d3drm_matrix {int _11; int _12; int _21; int _13; int _31; int _22; int _32; int _23; int _33; float _14; float _24; float _34; int _41; int _42; int _43; float _44; } ;

/* Variables and functions */

__attribute__((used)) static void d3drm_matrix_multiply_affine(struct d3drm_matrix *dst,
        const struct d3drm_matrix *src1, const struct d3drm_matrix *src2)
{
    struct d3drm_matrix tmp;

    tmp._11 = src1->_11 * src2->_11 + src1->_12 * src2->_21 + src1->_13 * src2->_31;
    tmp._12 = src1->_11 * src2->_12 + src1->_12 * src2->_22 + src1->_13 * src2->_32;
    tmp._13 = src1->_11 * src2->_13 + src1->_12 * src2->_23 + src1->_13 * src2->_33;
    tmp._14 = 0.0f;

    tmp._21 = src1->_21 * src2->_11 + src1->_22 * src2->_21 + src1->_23 * src2->_31;
    tmp._22 = src1->_21 * src2->_12 + src1->_22 * src2->_22 + src1->_23 * src2->_32;
    tmp._23 = src1->_21 * src2->_13 + src1->_22 * src2->_23 + src1->_23 * src2->_33;
    tmp._24 = 0.0f;

    tmp._31 = src1->_31 * src2->_11 + src1->_32 * src2->_21 + src1->_33 * src2->_31;
    tmp._32 = src1->_31 * src2->_12 + src1->_32 * src2->_22 + src1->_33 * src2->_32;
    tmp._33 = src1->_31 * src2->_13 + src1->_32 * src2->_23 + src1->_33 * src2->_33;
    tmp._34 = 0.0f;

    tmp._41 = src1->_41 * src2->_11 + src1->_42 * src2->_21 + src1->_43 * src2->_31 + src2->_41;
    tmp._42 = src1->_41 * src2->_12 + src1->_42 * src2->_22 + src1->_43 * src2->_32 + src2->_42;
    tmp._43 = src1->_41 * src2->_13 + src1->_42 * src2->_23 + src1->_43 * src2->_33 + src2->_43;
    tmp._44 = 1.0f;

    *dst = tmp;
}