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
 int ARRAY_SIZE (char**) ; 
 int host_byte (int) ; 
 char** hostbyte_table ; 

const char *scsi_hostbyte_string(int result)
{
	const char *hb_string = NULL;
	int hb = host_byte(result);

	if (hb < ARRAY_SIZE(hostbyte_table))
		hb_string = hostbyte_table[hb];
	return hb_string;
}