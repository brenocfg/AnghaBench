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
struct d3drm_matrix {float _11; float _21; float _31; float _41; float _12; float _22; float _32; float _42; float _13; float _23; float _33; float _43; float _14; float _24; float _34; float _44; } ;
struct TYPE_9__ {float z; } ;
struct TYPE_8__ {float x; } ;
struct TYPE_7__ {float y; } ;
struct TYPE_10__ {TYPE_3__ u3; TYPE_2__ u1; TYPE_1__ u2; } ;
typedef  TYPE_4__ D3DVECTOR ;

/* Variables and functions */
 int /*<<< orphan*/  D3DRMVectorNormalize (TYPE_4__*) ; 
 float cosf (float) ; 
 float sinf (float) ; 

__attribute__((used)) static void d3drm_matrix_set_rotation(struct d3drm_matrix *matrix, D3DVECTOR *axis, float theta)
{
    float sin_theta, cos_theta, vers_theta;

    D3DRMVectorNormalize(axis);
    sin_theta = sinf(theta);
    cos_theta = cosf(theta);
    vers_theta = 1.0f - cos_theta;

    matrix->_11 = vers_theta * axis->u1.x * axis->u1.x + cos_theta;
    matrix->_21 = vers_theta * axis->u1.x * axis->u2.y - sin_theta * axis->u3.z;
    matrix->_31 = vers_theta * axis->u1.x * axis->u3.z + sin_theta * axis->u2.y;
    matrix->_41 = 0.0f;

    matrix->_12 = vers_theta * axis->u2.y * axis->u1.x + sin_theta * axis->u3.z;
    matrix->_22 = vers_theta * axis->u2.y * axis->u2.y + cos_theta;
    matrix->_32 = vers_theta * axis->u2.y * axis->u3.z - sin_theta * axis->u1.x;
    matrix->_42 = 0.0f;

    matrix->_13 = vers_theta * axis->u3.z * axis->u1.x - sin_theta * axis->u2.y;
    matrix->_23 = vers_theta * axis->u3.z * axis->u2.y + sin_theta * axis->u1.x;
    matrix->_33 = vers_theta * axis->u3.z * axis->u3.z + cos_theta;
    matrix->_43 = 0.0f;

    matrix->_14 = 0.0f;
    matrix->_24 = 0.0f;
    matrix->_34 = 0.0f;
    matrix->_44 = 1.0f;
}