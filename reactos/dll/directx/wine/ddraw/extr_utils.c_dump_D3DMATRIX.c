#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  _44; int /*<<< orphan*/  _43; int /*<<< orphan*/  _42; int /*<<< orphan*/  _41; int /*<<< orphan*/  _34; int /*<<< orphan*/  _33; int /*<<< orphan*/  _32; int /*<<< orphan*/  _31; int /*<<< orphan*/  _24; int /*<<< orphan*/  _23; int /*<<< orphan*/  _22; int /*<<< orphan*/  _21; int /*<<< orphan*/  _14; int /*<<< orphan*/  _13; int /*<<< orphan*/  _12; int /*<<< orphan*/  _11; } ;
typedef  TYPE_1__ D3DMATRIX ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
dump_D3DMATRIX(const D3DMATRIX *mat)
{
    TRACE("  %f %f %f %f\n", mat->_11, mat->_12, mat->_13, mat->_14);
    TRACE("  %f %f %f %f\n", mat->_21, mat->_22, mat->_23, mat->_24);
    TRACE("  %f %f %f %f\n", mat->_31, mat->_32, mat->_33, mat->_34);
    TRACE("  %f %f %f %f\n", mat->_41, mat->_42, mat->_43, mat->_44);
}