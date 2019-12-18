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
typedef  int /*<<< orphan*/  ut32 ;
struct zip_stat {int /*<<< orphan*/ * name; } ;
struct zip {int dummy; } ;
typedef  int /*<<< orphan*/  RIOZipFileObj ;

/* Variables and functions */
 int /*<<< orphan*/ * r_io_zip_create_new_file (char const*,char const*,struct zip_stat*,int /*<<< orphan*/ ,int,int) ; 
 struct zip* r_io_zip_open_archive (char const*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  r_io_zip_slurp_file (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  zip_close (struct zip*) ; 
 scalar_t__ zip_get_num_files (struct zip*) ; 
 int /*<<< orphan*/  zip_stat_index (struct zip*,scalar_t__,int /*<<< orphan*/ ,struct zip_stat*) ; 
 int /*<<< orphan*/  zip_stat_init (struct zip_stat*) ; 

RIOZipFileObj* r_io_zip_alloc_zipfileobj(const char *archivename, const char *filename, ut32 perm, int mode, int rw) {
	RIOZipFileObj *zfo = NULL;
	ut64 i, num_entries;
	struct zip_stat sb;
	struct zip *zipArch = r_io_zip_open_archive (archivename, perm, mode, rw);
	if (!zipArch) {
		return NULL;
	}
	num_entries = zip_get_num_files (zipArch);

	for (i = 0; i < num_entries; i++) {
		zip_stat_init (&sb);
		zip_stat_index (zipArch, i, 0, &sb);
		if (sb.name != NULL) {
			if (strcmp (sb.name, filename) == 0) {
				zfo = r_io_zip_create_new_file (
					archivename, filename, &sb,
					perm, mode, rw);
				r_io_zip_slurp_file (zfo);
				break;
			}
		}
	}
	if (!zfo) {
		zfo = r_io_zip_create_new_file (archivename,
			filename, NULL, perm, mode, rw);
	}
	zip_close (zipArch);
	return zfo;
}