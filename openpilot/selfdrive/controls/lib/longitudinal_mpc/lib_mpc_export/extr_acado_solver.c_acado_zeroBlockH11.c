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
struct TYPE_2__ {double* H; } ;

/* Variables and functions */
 TYPE_1__ acadoWorkspace ; 

void acado_zeroBlockH11( int iRow, int iCol )
{
acadoWorkspace.H[(iRow * 23 + 69) + (iCol + 3)] = 0.0000000000000000e+00;
}