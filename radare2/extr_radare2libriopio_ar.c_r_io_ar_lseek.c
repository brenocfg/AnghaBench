#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int ut64 ;
struct TYPE_11__ {int base_priv; } ;
struct TYPE_10__ {int off; } ;
struct TYPE_9__ {TYPE_3__* data; } ;
typedef  TYPE_1__ RIODesc ;
typedef  TYPE_2__ RIO ;
typedef  TYPE_3__ RBuffer ;

/* Variables and functions */
#define  SEEK_CUR 130 
#define  SEEK_END 129 
#define  SEEK_SET 128 
 int /*<<< orphan*/  r_buf_seek (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int r_buf_size (TYPE_3__*) ; 
 int r_buf_tell (TYPE_3__*) ; 

__attribute__((used)) static ut64 r_io_ar_lseek(RIO *io, RIODesc *fd, ut64 offset, int whence) {
	RBuffer *b;
	ut64 seek_val = 0;

	if (!fd || !fd->data) {
		return -1;
	}

	b = fd->data;
	seek_val = r_buf_tell (b);

	switch (whence) {
	case SEEK_SET:
		seek_val = (r_buf_size (b) < offset)? r_buf_size (b) : offset;
		io->off = seek_val;
		r_buf_seek (b, b->base_priv + seek_val, 0);
		return seek_val;
	case SEEK_CUR:
		seek_val = (r_buf_size (b) < offset)? r_buf_size (b) : offset;
		io->off = seek_val;
		r_buf_seek (b, b->base_priv + seek_val, 0);
		return seek_val;
	case SEEK_END:
		seek_val = r_buf_size (b);
		io->off = seek_val;
		r_buf_seek (b, b->base_priv + seek_val, 0);
		return seek_val;
	}
	return seek_val;
}