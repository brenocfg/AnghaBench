#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ut64 ;
struct TYPE_6__ {scalar_t__ off; } ;
struct TYPE_5__ {int /*<<< orphan*/  buf; int /*<<< orphan*/  fd; scalar_t__ rawio; } ;
typedef  TYPE_1__ RIOMMapFileObj ;
typedef  TYPE_2__ RIO ;

/* Variables and functions */
 scalar_t__ R_MIN (scalar_t__,scalar_t__) ; 
#define  SEEK_CUR 130 
#define  SEEK_END 129 
#define  SEEK_SET 128 
 scalar_t__ UT64_MAX ; 
 scalar_t__ lseek (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  r_buf_seek (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ r_buf_size (int /*<<< orphan*/ ) ; 
 scalar_t__ r_buf_tell (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ut64 r_io_def_mmap_seek(RIO *io, RIOMMapFileObj *mmo, ut64 offset, int whence) {
	ut64 seek_val = UT64_MAX;

	if (!mmo) {
		return UT64_MAX;
	}
	if (mmo->rawio) {
		return lseek (mmo->fd, offset, whence);
	}
	if (!mmo->buf) {
		return UT64_MAX;
	}

	seek_val = r_buf_tell (mmo->buf);
	switch (whence) {
	case SEEK_SET:
		seek_val = R_MIN (r_buf_size (mmo->buf), offset);
		break;
	case SEEK_CUR:
		seek_val = R_MIN (r_buf_size (mmo->buf),
			(offset + r_buf_tell (mmo->buf)));
		break;
	case SEEK_END:
		seek_val = r_buf_size (mmo->buf);
		break;
	}
	r_buf_seek (mmo->buf, io->off = seek_val, 0);
	return seek_val;
}