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
typedef  int GLdouble ;

/* Variables and functions */

__attribute__((used)) static void __gluMultMatricesd(const GLdouble a[16], const GLdouble b[16],
				GLdouble r[16])
{
    int i, j;

    for (i = 0; i < 4; i++) {
	for (j = 0; j < 4; j++) {
	    r[i*4+j] = 
		a[i*4+0]*b[0*4+j] +
		a[i*4+1]*b[1*4+j] +
		a[i*4+2]*b[2*4+j] +
		a[i*4+3]*b[3*4+j];
	}
    }
}