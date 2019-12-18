#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
typedef  int ut64 ;
struct TYPE_4__ {int /*<<< orphan*/ * io; } ;
typedef  int /*<<< orphan*/  RIODesc ;
typedef  int /*<<< orphan*/  RIO ;
typedef  TYPE_1__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  R_FREE (int /*<<< orphan*/ *) ; 
 int ST32_MAX ; 
 int /*<<< orphan*/ * calloc (int,int) ; 
 int /*<<< orphan*/  eprintf (char*) ; 
 TYPE_1__* opencore (int /*<<< orphan*/ *) ; 
 scalar_t__ r_file_slurp (char const*,int*) ; 
 int /*<<< orphan*/  r_io_desc_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * r_io_open (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ r_io_read_at (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int r_io_size (int /*<<< orphan*/ *) ; 
 scalar_t__ strstr (char const*,char*) ; 

__attribute__((used)) static ut8 *slurp(RCore **c, const char *file, int *sz) {
	RIODesc *d;
	RIO *io;
	if (c && file && strstr (file, "://")) {
		ut8 *data = NULL;
		ut64 size;
		if (!*c) {
			*c = opencore (NULL);
		}
		if (!*c) {
			eprintf ("opencore failed\n");
			return NULL;
		}
		io = (*c)->io;
		d = r_io_open (io, file, 0, 0);
		if (!d) {
			return NULL;
		}
		size = r_io_size (io);
		if (size > 0 && size < ST32_MAX) {
			data = calloc (1, size);
			if (r_io_read_at (io, 0, data, size)) {
				if (sz) {
					*sz = size;
				}
			} else {
				eprintf ("slurp: read error\n");
				R_FREE (data);
			}
		} else {
			eprintf ("slurp: Invalid file size\n");
		}
		r_io_desc_close (d);
		return data;
	}
	return (ut8 *) r_file_slurp (file, sz);
}