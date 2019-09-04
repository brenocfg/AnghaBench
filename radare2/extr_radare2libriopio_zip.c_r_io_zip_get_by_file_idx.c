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
typedef  scalar_t__ ut64 ;
typedef  scalar_t__ ut32 ;
struct zip_stat {int /*<<< orphan*/  name; } ;
struct zip {int dummy; } ;

/* Variables and functions */
 scalar_t__ atoi (char const*) ; 
 struct zip* r_io_zip_open_archive (char const*,scalar_t__,int,int) ; 
 char* strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zip_close (struct zip*) ; 
 scalar_t__ zip_get_num_files (struct zip*) ; 
 int /*<<< orphan*/  zip_stat_index (struct zip*,scalar_t__,int /*<<< orphan*/ ,struct zip_stat*) ; 
 int /*<<< orphan*/  zip_stat_init (struct zip_stat*) ; 

char * r_io_zip_get_by_file_idx(const char * archivename, const char *idx, ut32 perm, int mode, int rw) {
	char *filename = NULL;
	ut64 i, num_entries;
	ut32 file_idx = -1;
	struct zip_stat sb;
	struct zip * zipArch = r_io_zip_open_archive (archivename, perm, mode, rw);
	if (!idx || !zipArch) {
		zip_close (zipArch);
		return filename;
	}
	num_entries = zip_get_num_files (zipArch);
	file_idx = atoi (idx);
	if ((file_idx == 0 && idx[0] != '0') || (file_idx >= num_entries)) {
		zip_close (zipArch);
		return filename;
	}
	for (i = 0; i < num_entries; i++) {
		zip_stat_init (&sb);
		zip_stat_index (zipArch, i, 0, &sb );
		if (file_idx == i) {
			filename = strdup (sb.name);
			break;
		}
	}
	zip_close (zipArch);
	return filename;
}