#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int ut64 ;
struct TYPE_8__ {int off; } ;
struct TYPE_7__ {TYPE_1__* data; } ;
struct TYPE_6__ {int /*<<< orphan*/  b; } ;
typedef  TYPE_1__ RIOZipFileObj ;
typedef  TYPE_2__ RIODesc ;
typedef  TYPE_3__ RIO ;

/* Variables and functions */
 int /*<<< orphan*/  R_BUF_SET ; 
#define  SEEK_CUR 130 
#define  SEEK_END 129 
#define  SEEK_SET 128 
 int /*<<< orphan*/  r_buf_seek (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int r_buf_size (int /*<<< orphan*/ ) ; 
 int r_buf_tell (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ut64 r_io_zip_lseek(RIO *io, RIODesc *fd, ut64 offset, int whence) {
	RIOZipFileObj *zfo;
	ut64 seek_val = 0;

	if (!fd || !fd->data) {
		return -1;
	}

	zfo = fd->data;
	seek_val = r_buf_tell (zfo->b);

	switch (whence) {
	case SEEK_SET:
		seek_val = (r_buf_size (zfo->b) < offset)? r_buf_size (zfo->b): offset;
		io->off = seek_val;
		r_buf_seek (zfo->b, seek_val, R_BUF_SET);
		return seek_val;
	case SEEK_CUR:
		seek_val = (r_buf_size (zfo->b) < (offset + r_buf_tell (zfo->b)))? r_buf_size (zfo->b): offset + r_buf_tell (zfo->b);
		io->off = seek_val;
		r_buf_seek (zfo->b, seek_val, R_BUF_SET);
		return seek_val;
	case SEEK_END:
		seek_val = r_buf_size (zfo->b);
		io->off = seek_val;
		r_buf_seek (zfo->b, seek_val, R_BUF_SET);
		return seek_val;
	}
	return seek_val;
}