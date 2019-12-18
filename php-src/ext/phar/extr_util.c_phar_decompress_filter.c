#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_3__ {int old_flags; int flags; scalar_t__ is_modified; } ;
typedef  TYPE_1__ phar_entry_info ;

/* Variables and functions */
#define  PHAR_ENT_COMPRESSED_BZ2 129 
#define  PHAR_ENT_COMPRESSED_GZ 128 
 int PHAR_ENT_COMPRESSION_MASK ; 

char * phar_decompress_filter(phar_entry_info * entry, int return_unknown) /* {{{ */
{
	uint32_t flags;

	if (entry->is_modified) {
		flags = entry->old_flags;
	} else {
		flags = entry->flags;
	}

	switch (flags & PHAR_ENT_COMPRESSION_MASK) {
		case PHAR_ENT_COMPRESSED_GZ:
			return "zlib.inflate";
		case PHAR_ENT_COMPRESSED_BZ2:
			return "bzip2.decompress";
		default:
			return return_unknown ? "unknown" : NULL;
	}
}