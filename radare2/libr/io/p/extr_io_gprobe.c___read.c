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
typedef  int /*<<< orphan*/  ut8 ;
struct TYPE_5__ {scalar_t__ data; } ;
struct TYPE_4__ {scalar_t__ offset; int /*<<< orphan*/  gport; } ;
typedef  TYPE_1__ RIOGprobe ;
typedef  TYPE_2__ RIODesc ;
typedef  int /*<<< orphan*/  RIO ;

/* Variables and functions */
 scalar_t__ GPROBE_SIZE ; 
 int gprobe_read (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int __read (RIO *io, RIODesc *fd, ut8 *buf, int count) {
	int res;
	RIOGprobe *gprobe;
	int has_read = 0;

	if (!fd || !fd->data || !buf) {
		return -1;
	}

	gprobe = (RIOGprobe *)fd->data;

	if ((gprobe->offset + count) > GPROBE_SIZE) {
		count = GPROBE_SIZE - gprobe->offset;
	}

	while (has_read < count) {
		res = gprobe_read (&gprobe->gport, gprobe->offset, buf + has_read, count - has_read);
		if (res <= 0) {
			return -1;
		}
		gprobe->offset += res;
		has_read += res;
	}

	return has_read;
}