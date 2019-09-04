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
typedef  scalar_t__ ut64 ;
struct TYPE_3__ {scalar_t__ off; } ;
typedef  int /*<<< orphan*/  RIODesc ;
typedef  TYPE_1__ RIO ;

/* Variables and functions */
#define  R_IO_SEEK_CUR 130 
#define  R_IO_SEEK_END 129 
#define  R_IO_SEEK_SET 128 
 scalar_t__ UT64_MAX ; 

__attribute__((used)) static ut64 __lseek(RIO *io, RIODesc *fd, ut64 offset, int whence) {
	switch (whence) {
	case R_IO_SEEK_SET:
		return offset;
	case R_IO_SEEK_CUR:
		return io->off + offset;
	case R_IO_SEEK_END:
		return UT64_MAX;
	default:
		return offset;
	}
}