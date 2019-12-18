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
typedef  int /*<<< orphan*/  ut8 ;
struct zip_stat {int /*<<< orphan*/  size; } ;
struct zip_file {int dummy; } ;
struct zip {int dummy; } ;
struct TYPE_3__ {int entry; int opened; scalar_t__ b; int /*<<< orphan*/  rw; int /*<<< orphan*/  mode; int /*<<< orphan*/  perm; int /*<<< orphan*/  archivename; } ;
typedef  TYPE_1__ RIOZipFileObj ;

/* Variables and functions */
 int /*<<< orphan*/ * calloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ r_buf_new () ; 
 int /*<<< orphan*/  r_buf_set_bytes (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct zip* r_io_zip_open_archive (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zip_close (struct zip*) ; 
 int /*<<< orphan*/  zip_fclose (struct zip_file*) ; 
 struct zip_file* zip_fopen_index (struct zip*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zip_fread (struct zip_file*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zip_stat_index (struct zip*,int,int /*<<< orphan*/ ,struct zip_stat*) ; 
 int /*<<< orphan*/  zip_stat_init (struct zip_stat*) ; 

__attribute__((used)) static int r_io_zip_slurp_file(RIOZipFileObj *zfo) {
	struct zip_file *zFile = NULL;
	struct zip *zipArch;
	struct zip_stat sb;
	bool res = false;
	if (!zfo) {
		return res;
	}
	zipArch = r_io_zip_open_archive (
		zfo->archivename, zfo->perm,
		zfo->mode, zfo->rw);

	if (zipArch && zfo && zfo->entry != -1) {
		zFile = zip_fopen_index (zipArch, zfo->entry, 0);
		if (!zfo->b) {
			zfo->b = r_buf_new ();
		}
		zip_stat_init (&sb);
		if (zFile && zfo->b && !zip_stat_index (zipArch, zfo->entry, 0, &sb)) {
			ut8 *buf = calloc (1, sb.size);
			if (buf) {
				zip_fread (zFile, buf, sb.size);
				r_buf_set_bytes (zfo->b, buf, sb.size);
				res = true;
				zfo->opened = true;
				free (buf);
			}
		}
		zip_fclose (zFile);
	}
	zip_close (zipArch);
	return res;
}