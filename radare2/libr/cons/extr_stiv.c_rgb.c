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
 int R_DIM (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int rgb(int r, int g, int b) {
	r = R_DIM (r, 0, 255);
	g = R_DIM (g, 0, 255);
	b = R_DIM (b, 0, 255);
	r = (int)(r/50.6); 
	g = (int)(g/50.6);
	b = (int)(b/50.6);
	return 16 + (r*36) + (g*6) + b;
}