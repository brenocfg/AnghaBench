#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ut64 ;
typedef  scalar_t__ ut32 ;
struct TYPE_6__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ RIODesc ;
typedef  int /*<<< orphan*/  RIO ;

/* Variables and functions */
#define  SEEK_CUR 130 
#define  SEEK_END 129 
#define  SEEK_SET 128 
 scalar_t__ _io_malloc_off (TYPE_1__*) ; 
 int /*<<< orphan*/  _io_malloc_set_off (TYPE_1__*,scalar_t__) ; 
 scalar_t__ _io_malloc_sz (TYPE_1__*) ; 

__attribute__((used)) static ut64 __lseek(RIO* io, RIODesc *fd, ut64 offset, int whence) {
	ut64 r_offset = offset;
	if (!fd || !fd->data) {
		return offset;
	}
	ut32 mallocsz = _io_malloc_sz (fd);
	switch (whence) {
	case SEEK_SET:
		r_offset = (offset <= mallocsz) ? offset : mallocsz;
		break;
	case SEEK_CUR:
		r_offset = (_io_malloc_off (fd) + offset <= mallocsz ) ? _io_malloc_off (fd) + offset : mallocsz;
		break;
	case SEEK_END:
		r_offset = _io_malloc_sz (fd);
		break;
	}
	_io_malloc_set_off (fd, r_offset);
	return r_offset;
}