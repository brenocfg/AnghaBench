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
 short DEVCG_DEV_ALL ; 
 short DEVCG_DEV_BLOCK ; 
 short DEVCG_DEV_CHAR ; 

__attribute__((used)) static char type_to_char(short type)
{
	if (type == DEVCG_DEV_ALL)
		return 'a';
	if (type == DEVCG_DEV_CHAR)
		return 'c';
	if (type == DEVCG_DEV_BLOCK)
		return 'b';
	return 'X';
}