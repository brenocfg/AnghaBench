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
typedef  int zip_flags_t ;
struct zip_dirent {scalar_t__ uncomp_size; scalar_t__ comp_size; scalar_t__ offset; } ;

/* Variables and functions */
 int ZIP_FL_CENTRAL ; 
 scalar_t__ ZIP_UINT32_MAX ; 

int
_zip_dirent_needs_zip64(const struct zip_dirent *de, zip_flags_t flags)
{
    if (de->uncomp_size >= ZIP_UINT32_MAX || de->comp_size >= ZIP_UINT32_MAX
	|| ((flags & ZIP_FL_CENTRAL) && de->offset >= ZIP_UINT32_MAX))
	return 1;

    return 0;
}