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
struct TYPE_3__ {int /*<<< orphan*/ * data; } ;
typedef  int /*<<< orphan*/  RIOZipFileObj ;
typedef  TYPE_1__ RIODesc ;

/* Variables and functions */
 int /*<<< orphan*/  r_io_zip_free_zipfileobj (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int r_io_zip_close(RIODesc *fd) {
	RIOZipFileObj *zfo;
	if (!fd || !fd->data) {
		return -1;
	}
	zfo = fd->data;
	r_io_zip_free_zipfileobj (zfo);
	zfo = fd->data = NULL;
	return 0;
}