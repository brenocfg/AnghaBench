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
typedef  int real_t ;
struct TYPE_2__ {int* QN1; } ;

/* Variables and functions */
 TYPE_1__ acadoWorkspace ; 

void acado_multQN1d( real_t* const QN1, real_t* const dOld, real_t* const dNew )
{
dNew[0] = + acadoWorkspace.QN1[0]*dOld[0] + acadoWorkspace.QN1[1]*dOld[1] + acadoWorkspace.QN1[2]*dOld[2] + acadoWorkspace.QN1[3]*dOld[3];
dNew[1] = + acadoWorkspace.QN1[4]*dOld[0] + acadoWorkspace.QN1[5]*dOld[1] + acadoWorkspace.QN1[6]*dOld[2] + acadoWorkspace.QN1[7]*dOld[3];
dNew[2] = + acadoWorkspace.QN1[8]*dOld[0] + acadoWorkspace.QN1[9]*dOld[1] + acadoWorkspace.QN1[10]*dOld[2] + acadoWorkspace.QN1[11]*dOld[3];
dNew[3] = + acadoWorkspace.QN1[12]*dOld[0] + acadoWorkspace.QN1[13]*dOld[1] + acadoWorkspace.QN1[14]*dOld[2] + acadoWorkspace.QN1[15]*dOld[3];
}