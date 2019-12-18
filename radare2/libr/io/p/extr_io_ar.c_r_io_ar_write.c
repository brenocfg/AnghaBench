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
typedef  int /*<<< orphan*/  ut8 ;
struct TYPE_6__ {int /*<<< orphan*/  off; } ;
struct TYPE_5__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ RIODesc ;
typedef  TYPE_2__ RIO ;
typedef  int /*<<< orphan*/  RBuffer ;

/* Variables and functions */
 int ar_write_at (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int) ; 

__attribute__((used)) static int r_io_ar_write(RIO *io, RIODesc *fd, const ut8 *buf, int count) {
	RBuffer *b = NULL;
	if (!fd || !fd->data || !buf) {
		return -1;
	}
	return ar_write_at (b, io->off, (void *) buf, count);
}