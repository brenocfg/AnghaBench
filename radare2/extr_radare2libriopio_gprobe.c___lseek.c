#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ut64 ;
struct TYPE_5__ {scalar_t__ data; } ;
struct TYPE_4__ {scalar_t__ offset; } ;
typedef  TYPE_1__ RIOGprobe ;
typedef  TYPE_2__ RIODesc ;
typedef  int /*<<< orphan*/  RIO ;

/* Variables and functions */
 scalar_t__ GPROBE_SIZE ; 
#define  SEEK_CUR 130 
#define  SEEK_END 129 
#define  SEEK_SET 128 

__attribute__((used)) static ut64 __lseek (RIO *io, RIODesc *fd, ut64 offset, int whence) {
	RIOGprobe *gprobe;
	if (!fd || !fd->data) {
		return offset;
	}
	gprobe = (RIOGprobe *)fd->data;
	switch (whence) {
	case SEEK_SET:
		if (offset >= GPROBE_SIZE) {
			return gprobe->offset = GPROBE_SIZE - 1;
		}
		return gprobe->offset = offset;
	case SEEK_CUR:
		if ((gprobe->offset + offset) >= GPROBE_SIZE) {
			return gprobe->offset = GPROBE_SIZE - 1;
		}
		return gprobe->offset += offset;
	case SEEK_END:
		return gprobe->offset = GPROBE_SIZE - 1;
	}
	return offset;
}