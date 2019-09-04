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
 int PREFIX_SIZE ; 

__attribute__((used)) static int remaining(int wrote)
{
	if (PREFIX_SIZE - wrote > 0)
		return PREFIX_SIZE - wrote;
	return 0;
}