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
 unsigned char DT_UNKNOWN ; 
 unsigned int FT_MAX ; 
 unsigned char* fs_dtype_by_ftype ; 

unsigned char fs_ftype_to_dtype(unsigned int filetype)
{
	if (filetype >= FT_MAX)
		return DT_UNKNOWN;

	return fs_dtype_by_ftype[filetype];
}