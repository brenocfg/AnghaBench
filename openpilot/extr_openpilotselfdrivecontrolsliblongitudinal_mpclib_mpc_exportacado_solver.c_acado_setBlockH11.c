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

void acado_setBlockH11( int iRow, int iCol, real_t* const Gu1, real_t* const Gu2 )
{
acadoWorkspace.H[(iRow * 23 + 69) + (iCol + 3)] += + Gu1[0]*Gu2[0] + Gu1[1]*Gu2[1] + Gu1[2]*Gu2[2];
}