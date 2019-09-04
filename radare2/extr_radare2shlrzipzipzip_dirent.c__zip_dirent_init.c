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
struct zip_dirent {int version_madeby; int version_needed; scalar_t__ offset; scalar_t__ ext_attrib; scalar_t__ int_attrib; scalar_t__ disk_number; int /*<<< orphan*/ * comment; int /*<<< orphan*/ * extra_fields; int /*<<< orphan*/ * filename; scalar_t__ uncomp_size; scalar_t__ comp_size; scalar_t__ crc; scalar_t__ last_mod; int /*<<< orphan*/  comp_method; scalar_t__ bitflags; scalar_t__ cloned; scalar_t__ local_extra_fields_read; scalar_t__ changed; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZIP_CM_DEFAULT ; 

void
_zip_dirent_init(struct zip_dirent *de)
{
    de->changed = 0;
    de->local_extra_fields_read = 0;
    de->cloned = 0;

    de->version_madeby = 20;
    de->version_needed = 20; /* 2.0 */
    de->bitflags = 0;
    de->comp_method = ZIP_CM_DEFAULT;
    de->last_mod = 0;
    de->crc = 0;
    de->comp_size = 0;
    de->uncomp_size = 0;
    de->filename = NULL;
    de->extra_fields = NULL;
    de->comment = NULL;
    de->disk_number = 0;
    de->int_attrib = 0;
    de->ext_attrib = 0;
    de->offset = 0;
}