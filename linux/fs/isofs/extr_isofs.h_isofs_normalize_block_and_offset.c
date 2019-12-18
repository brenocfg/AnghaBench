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
struct iso_directory_record {int* flags; int /*<<< orphan*/  ext_attr_length; int /*<<< orphan*/  extent; } ;

/* Variables and functions */
 scalar_t__ isonum_711 (int /*<<< orphan*/ ) ; 
 scalar_t__ isonum_733 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
isofs_normalize_block_and_offset(struct iso_directory_record* de,
				 unsigned long *block,
				 unsigned long *offset)
{
	/* Only directories are normalized. */
	if (de->flags[0] & 2) {
		*offset = 0;
		*block = (unsigned long)isonum_733(de->extent)
			+ (unsigned long)isonum_711(de->ext_attr_length);
	}
}