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
 float acosf (float) ; 
 scalar_t__ ceilf (float) ; 
 int nvg__maxi (int,int) ; 

__attribute__((used)) static int nvg__curveDivs(float r, float arc, float tol)
{
	float da = acosf(r / (r + tol)) * 2.0f;
	return nvg__maxi(2, (int)ceilf(arc / da));
}