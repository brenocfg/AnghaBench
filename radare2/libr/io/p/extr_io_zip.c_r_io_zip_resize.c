#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut64 ;
struct TYPE_7__ {TYPE_1__* data; } ;
struct TYPE_6__ {int modified; } ;
typedef  TYPE_1__ RIOZipFileObj ;
typedef  TYPE_2__ RIODesc ;
typedef  int /*<<< orphan*/  RIO ;

/* Variables and functions */
 int /*<<< orphan*/  r_io_zip_flush_file (TYPE_1__*) ; 
 scalar_t__ r_io_zip_truncate_buf (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool r_io_zip_resize(RIO *io, RIODesc *fd, ut64 size) {
	RIOZipFileObj *zfo;
	if (!fd || !fd->data) {
		return false;
	}
	zfo = fd->data;
	if (r_io_zip_truncate_buf (zfo, size)) {
		zfo->modified = 1;
		r_io_zip_flush_file (zfo);
		return true;
	}
	return false;
}