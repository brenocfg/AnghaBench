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

__attribute__((used)) static int 
demunge_int32 (unsigned char* src, int src_size)

{
	int i;
 	int outval = 0;
	
 	for (i = src_size - 1; i >= 0; i--) {
		outval=(outval<<7)+src[i];
	}

	return outval;
}