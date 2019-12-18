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
struct TYPE_2__ {int* H; } ;

/* Variables and functions */
 TYPE_1__ acadoWorkspace ; 

void acado_multCTQC( real_t* const Gx1, real_t* const Gx2 )
{
acadoWorkspace.H[0] += + Gx1[0]*Gx2[0] + Gx1[3]*Gx2[3] + Gx1[6]*Gx2[6];
acadoWorkspace.H[1] += + Gx1[0]*Gx2[1] + Gx1[3]*Gx2[4] + Gx1[6]*Gx2[7];
acadoWorkspace.H[2] += + Gx1[0]*Gx2[2] + Gx1[3]*Gx2[5] + Gx1[6]*Gx2[8];
acadoWorkspace.H[23] += + Gx1[1]*Gx2[0] + Gx1[4]*Gx2[3] + Gx1[7]*Gx2[6];
acadoWorkspace.H[24] += + Gx1[1]*Gx2[1] + Gx1[4]*Gx2[4] + Gx1[7]*Gx2[7];
acadoWorkspace.H[25] += + Gx1[1]*Gx2[2] + Gx1[4]*Gx2[5] + Gx1[7]*Gx2[8];
acadoWorkspace.H[46] += + Gx1[2]*Gx2[0] + Gx1[5]*Gx2[3] + Gx1[8]*Gx2[6];
acadoWorkspace.H[47] += + Gx1[2]*Gx2[1] + Gx1[5]*Gx2[4] + Gx1[8]*Gx2[7];
acadoWorkspace.H[48] += + Gx1[2]*Gx2[2] + Gx1[5]*Gx2[5] + Gx1[8]*Gx2[8];
}