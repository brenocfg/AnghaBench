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
typedef  int /*<<< orphan*/  ut64 ;
struct zip_source {int dummy; } ;
struct zip {int dummy; } ;
struct TYPE_3__ {int entry; scalar_t__ name; int /*<<< orphan*/  b; int /*<<< orphan*/  rw; int /*<<< orphan*/  mode; int /*<<< orphan*/  perm; int /*<<< orphan*/  archivename; } ;
typedef  TYPE_1__ RIOZipFileObj ;

/* Variables and functions */
 int /*<<< orphan*/ * r_buf_data (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct zip* r_io_zip_open_archive (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ zip_add (struct zip*,scalar_t__,struct zip_source*) ; 
 int /*<<< orphan*/  zip_close (struct zip*) ; 
 int zip_name_locate (struct zip*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ zip_replace (struct zip*,int,struct zip_source*) ; 
 struct zip_source* zip_source_buffer (struct zip*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zip_source_free (struct zip_source*) ; 

int r_io_zip_flush_file(RIOZipFileObj *zfo) {
	int res = false;
	struct zip * zipArch;

	if (!zfo) {
		return res;
	}

	zipArch = r_io_zip_open_archive (
		zfo->archivename, zfo->perm, zfo->mode, zfo->rw);
	if (!zipArch) {
		return res;
	}

	ut64 tmpsz;
	const ut8 *tmp = r_buf_data (zfo->b, &tmpsz);
	struct zip_source *s = zip_source_buffer (zipArch, tmp, tmpsz, 0);
	if (s && zfo->entry != -1) {
		if (zip_replace(zipArch, zfo->entry, s) == 0) {
			res = true;
		}
	} else if (s && zfo->name) {
		if (zip_add (zipArch, zfo->name, s) == 0) {
			zfo->entry = zip_name_locate (zipArch, zfo->name, 0);
			res = true;
		}
	}
	// s (zip_source) is freed when the archive is closed, i think - dso
	zip_close (zipArch);
	if (s) {
		zip_source_free (s);
	}
	return res;
}