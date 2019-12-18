#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
typedef  int /*<<< orphan*/  ut64 ;
struct TYPE_5__ {scalar_t__ extra_cmdline; scalar_t__* id; scalar_t__ cmdline; scalar_t__ name; } ;
struct TYPE_4__ {int /*<<< orphan*/  buf; TYPE_2__ bi; } ;
typedef  int /*<<< orphan*/  Sdb ;
typedef  TYPE_1__ BootImageObj ;
typedef  TYPE_2__ BootImage ;

/* Variables and functions */
 int /*<<< orphan*/  BOOT_ARGS_SIZE ; 
 int /*<<< orphan*/  BOOT_EXTRA_ARGS_SIZE ; 
 int /*<<< orphan*/  BOOT_NAME_SIZE ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  r_buf_read_at (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int r_buf_size (int /*<<< orphan*/ ) ; 
 char* r_str_ndup (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdb_num_set (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdb_set (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bootimg_header_load(BootImageObj *obj, Sdb *db) {
	char *n;
	int i;
	if (r_buf_size (obj->buf) < sizeof (BootImage)) {
		return false;
	}
	// TODO make it endian-safe (void)r_buf_fread_at (buf, 0, (ut8*)bi, "IIiiiiiiiiiiii", 1);
	BootImage *bi = &obj->bi;
	(void) r_buf_read_at (obj->buf, 0, (ut8 *)bi, sizeof (BootImage));
	if ((n = r_str_ndup ((char *) bi->name, BOOT_NAME_SIZE))) {
		sdb_set (db, "name", n, 0);
		free (n);
	}
	if ((n = r_str_ndup ((char *) bi->cmdline, BOOT_ARGS_SIZE))) {
		sdb_set (db, "cmdline", n, 0);
		free (n);
	}
	for (i = 0; i < 8; i++) {
		sdb_num_set (db, "id", (ut64) bi->id[i], 0);
	}
	if ((n = r_str_ndup ((char *) bi->extra_cmdline, BOOT_EXTRA_ARGS_SIZE))) {
		sdb_set (db, "extra_cmdline", n, 0);
		free (n);
	}
	return true;
}