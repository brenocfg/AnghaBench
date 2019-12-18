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
struct zip_dirent {scalar_t__ version_needed; int bitflags; scalar_t__ comp_method; scalar_t__ last_mod; scalar_t__ crc; scalar_t__ comp_size; scalar_t__ uncomp_size; int /*<<< orphan*/  filename; } ;

/* Variables and functions */
 int ZIP_GPBF_DATA_DESCRIPTOR ; 
 int /*<<< orphan*/  _zip_string_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
_zip_headercomp(const struct zip_dirent *central, const struct zip_dirent *local)
{
    if ((central->version_needed != local->version_needed)
#if 0
	/* some zip-files have different values in local
	   and global headers for the bitflags */
	|| (central->bitflags != local->bitflags)
#endif
	|| (central->comp_method != local->comp_method)
	|| (central->last_mod != local->last_mod)
	|| !_zip_string_equal(central->filename, local->filename)) {
	return -1;
    }


    if ((central->crc != local->crc) || (central->comp_size != local->comp_size)
	|| (central->uncomp_size != local->uncomp_size)) {
	/* InfoZip stores valid values in local header even when data descriptor is used.
	   This is in violation of the appnote. */
	if (((local->bitflags & ZIP_GPBF_DATA_DESCRIPTOR) == 0
	     || local->crc != 0 || local->comp_size != 0 || local->uncomp_size != 0))
	    return -1;
    }

    return 0;
}