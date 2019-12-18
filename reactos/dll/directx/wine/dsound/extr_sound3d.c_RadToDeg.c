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
typedef  int D3DVALUE ;

/* Variables and functions */
 int M_PI ; 
 int /*<<< orphan*/  TRACE (char*,int,int) ; 

__attribute__((used)) static inline D3DVALUE RadToDeg (D3DVALUE angle)
{
	D3DVALUE newangle;
	newangle = angle * (360/(2*M_PI));
	TRACE("%f rad = %f deg\n", angle, newangle);
	return newangle;
}