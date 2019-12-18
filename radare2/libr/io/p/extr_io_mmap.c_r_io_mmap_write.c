#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
typedef  scalar_t__ ut64 ;
struct TYPE_9__ {scalar_t__ off; } ;
struct TYPE_8__ {TYPE_1__* data; } ;
struct TYPE_7__ {int flags; int /*<<< orphan*/  filename; int /*<<< orphan*/  buf; } ;
typedef  TYPE_1__ RIOMMapFileObj ;
typedef  TYPE_2__ RIODesc ;
typedef  TYPE_3__ RIO ;

/* Variables and functions */
 int R_PERM_W ; 
 int /*<<< orphan*/  eprintf (char*) ; 
 scalar_t__ r_buf_size (int /*<<< orphan*/ ) ; 
 int r_file_mmap_write (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  r_file_truncate (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  r_io_mmap_refresh_buf (TYPE_1__*) ; 

__attribute__((used)) static int r_io_mmap_write(RIO *io, RIODesc *fd, const ut8 *buf, int count) {
	RIOMMapFileObj *mmo;
	int len = count;
	ut64 addr;

	if (!io || !fd || !fd->data || !buf) {
		return -1;
	}
	mmo = fd->data;
	addr = io->off;
	if ( !(mmo->flags & R_PERM_W)) {
		return -1;
	}
	if ( (count + addr > r_buf_size (mmo->buf)) || r_buf_size (mmo->buf) == 0) {
		ut64 sz = count + addr;
		r_file_truncate (mmo->filename, sz);
	}
	len = r_file_mmap_write (mmo->filename, io->off, buf, len);
	if (!r_io_mmap_refresh_buf (mmo) ) {
		eprintf ("io_mmap: failed to refresh the mmap backed buffer.\n");
		// XXX - not sure what needs to be done here (error handling).
	}
	return len;
}