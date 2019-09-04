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
struct zip_stat {int /*<<< orphan*/  name; } ;
struct zip {int dummy; } ;
typedef  int /*<<< orphan*/  RList ;

/* Variables and functions */
 int /*<<< orphan*/  free ; 
 struct zip* r_io_zip_open_archive (char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  r_list_append (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * r_list_newf (int /*<<< orphan*/ ) ; 
 char* strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zip_close (struct zip*) ; 
 scalar_t__ zip_get_num_files (struct zip*) ; 
 int /*<<< orphan*/  zip_stat_index (struct zip*,scalar_t__,int /*<<< orphan*/ ,struct zip_stat*) ; 
 int /*<<< orphan*/  zip_stat_init (struct zip_stat*) ; 

RList * r_io_zip_get_files(char *archivename, ut32 perm, int mode, int rw) {
	struct zip *zipArch = r_io_zip_open_archive (archivename, perm, mode, rw);
	ut64 num_entries = 0, i = 0;
	RList *files = NULL;
	struct zip_stat sb;
	char *name;
	if (zipArch) {
		files = r_list_newf (free);
		if (!files) {
			zip_close (zipArch);
			return NULL;
		}
		num_entries = zip_get_num_files (zipArch);
		for (i = 0; i < num_entries; i++) {
			zip_stat_init (&sb);
			zip_stat_index (zipArch, i, 0, &sb);
			if ((name = strdup (sb.name))) {
				r_list_append (files, name);
			}
		}
	}
	zip_close (zipArch);
	return files;
}