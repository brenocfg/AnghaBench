#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct d3drm_matrix {int _11; int _21; int _31; int _41; int _12; int _22; int _32; int _42; int _13; int _23; int _33; int _43; } ;
struct TYPE_9__ {int z; } ;
struct TYPE_8__ {int y; } ;
struct TYPE_7__ {int x; } ;
struct TYPE_10__ {TYPE_3__ u3; TYPE_2__ u2; TYPE_1__ u1; } ;
typedef  TYPE_4__ D3DVECTOR ;

/* Variables and functions */

__attribute__((used)) static void d3drm_vector_transform_affine(D3DVECTOR *dst, const D3DVECTOR *v, const struct d3drm_matrix *m)
{
    D3DVECTOR tmp;

    tmp.u1.x = v->u1.x * m->_11 + v->u2.y * m->_21 + v->u3.z * m->_31 + m->_41;
    tmp.u2.y = v->u1.x * m->_12 + v->u2.y * m->_22 + v->u3.z * m->_32 + m->_42;
    tmp.u3.z = v->u1.x * m->_13 + v->u2.y * m->_23 + v->u3.z * m->_33 + m->_43;

    *dst = tmp;
}