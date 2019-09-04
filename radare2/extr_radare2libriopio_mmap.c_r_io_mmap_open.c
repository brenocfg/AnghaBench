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
struct TYPE_4__ {int /*<<< orphan*/  filename; } ;
typedef  TYPE_1__ RIOMMapFileObj ;
typedef  int /*<<< orphan*/  RIODesc ;
typedef  int /*<<< orphan*/  RIO ;

/* Variables and functions */
 int /*<<< orphan*/ * r_io_desc_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,TYPE_1__*) ; 
 TYPE_1__* r_io_mmap_create_new_file (int /*<<< orphan*/ *,char const*,int,int) ; 
 int /*<<< orphan*/  r_io_plugin_mmap ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 

__attribute__((used)) static RIODesc *r_io_mmap_open(RIO *io, const char *file, int flags, int mode) {
	if (!strncmp (file, "mmap://", 7)) {
		file += 7;
	}
	RIOMMapFileObj *mmo = r_io_mmap_create_new_file (io, file, mode, flags);
	return mmo? r_io_desc_new (io, &r_io_plugin_mmap, mmo->filename, flags, mode, mmo): NULL;
}