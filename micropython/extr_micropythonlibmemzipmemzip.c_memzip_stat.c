#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  last_mod_time; int /*<<< orphan*/  last_mod_date; int /*<<< orphan*/  uncompressed_size; } ;
struct TYPE_5__ {int is_dir; int /*<<< orphan*/  last_mod_time; int /*<<< orphan*/  last_mod_date; int /*<<< orphan*/  file_size; } ;
typedef  int /*<<< orphan*/  MEMZIP_RESULT ;
typedef  TYPE_1__ MEMZIP_FILE_INFO ;
typedef  TYPE_2__ MEMZIP_FILE_HDR ;

/* Variables and functions */
 int /*<<< orphan*/  MZ_NO_FILE ; 
 int /*<<< orphan*/  MZ_OK ; 
 TYPE_2__* memzip_find_file_header (char const*) ; 
 scalar_t__ memzip_is_dir (char const*) ; 

MEMZIP_RESULT memzip_stat(const char *path, MEMZIP_FILE_INFO *info) {
    const MEMZIP_FILE_HDR *file_hdr = memzip_find_file_header(path);
    if (file_hdr == NULL) {
        if (memzip_is_dir(path)) {
            info->file_size = 0;
            info->last_mod_date = 0;
            info->last_mod_time = 0;
            info->is_dir = 1;
            return MZ_OK;
        }
        return MZ_NO_FILE;
    }
    info->file_size = file_hdr->uncompressed_size;
    info->last_mod_date = file_hdr->last_mod_date;
    info->last_mod_time = file_hdr->last_mod_time;
    info->is_dir = 0;

    return MZ_OK;
}