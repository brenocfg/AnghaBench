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
 unsigned int min (unsigned int,unsigned int) ; 

__attribute__((used)) static unsigned int max_bytes(unsigned int start, unsigned int len,
			      unsigned int boundary)
{
	return min(boundary - (start & (boundary - 1)), len);
}