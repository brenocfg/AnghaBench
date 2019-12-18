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

/* Variables and functions */
 int S_iBottom ; 
 int S_iLeft ; 
 int S_iRight ; 
 int S_iTop ; 
 int /*<<< orphan*/  window (int,int,int,int) ; 

__attribute__((used)) static void
mywindow(int iLeft, int iTop, int iRight, int iBottom)
{
    S_iLeft = iLeft;
    S_iTop = iTop;
    S_iRight = iRight;
    S_iBottom = iBottom;
    window(iLeft, iTop, iRight, iBottom);
}