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
typedef  scalar_t__ ut64 ;
typedef  scalar_t__ st64 ;
struct TYPE_4__ {int rawio; int fd; scalar_t__ nocache; int /*<<< orphan*/  mode; int /*<<< orphan*/  perm; int /*<<< orphan*/  filename; int /*<<< orphan*/ * buf; int /*<<< orphan*/ * io_backref; } ;
typedef  TYPE_1__ RIOMMapFileObj ;
typedef  int /*<<< orphan*/  RIO ;

/* Variables and functions */
 int /*<<< orphan*/  F_NOCACHE ; 
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ ST32_MAX ; 
 void* __io_posix_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fcntl (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r_buf_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * r_buf_new_mmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ r_buf_tell (int /*<<< orphan*/ *) ; 
 scalar_t__ r_file_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_io_def_mmap_seek (int /*<<< orphan*/ *,TYPE_1__*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int r_io_def_mmap_refresh_def_mmap_buf(RIOMMapFileObj *mmo) {
	RIO* io = mmo->io_backref;
	ut64 cur;
	if (mmo->buf) {
		cur = r_buf_tell (mmo->buf);
		r_buf_free (mmo->buf);
		mmo->buf = NULL;
	} else {
		cur = 0;
	}
	st64 sz = r_file_size (mmo->filename);
	if (sz > ST32_MAX) {
		// Do not use mmap if the file is huge
		mmo->rawio = 1;
	}
	if (mmo->rawio) {
		mmo->fd = __io_posix_open (mmo->filename, mmo->perm, mmo->mode);
		if (mmo->nocache) {
#ifdef F_NOCACHE
			fcntl (mmo->fd, F_NOCACHE, 1);
#endif
		}
		return (mmo->fd != -1);
	}
	mmo->buf = r_buf_new_mmap (mmo->filename, mmo->perm);
	if (mmo->buf) {
		r_io_def_mmap_seek (io, mmo, cur, SEEK_SET);
		return true;
	} else {
		mmo->rawio = 1;
		mmo->fd = __io_posix_open (mmo->filename, mmo->perm, mmo->mode);
		if (mmo->nocache) {
#ifdef F_NOCACHE
			fcntl (mmo->fd, F_NOCACHE, 1);
#endif
		}
		return (mmo->fd != -1);
	}
	return false;
}