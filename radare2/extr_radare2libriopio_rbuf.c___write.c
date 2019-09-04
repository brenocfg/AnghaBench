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
typedef  int /*<<< orphan*/  ut8 ;
struct TYPE_3__ {int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ RIODesc ;
typedef  int /*<<< orphan*/  RIO ;
typedef  int /*<<< orphan*/  RBuffer ;

/* Variables and functions */
 int r_buf_write (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int __write(RIO *io, RIODesc *fd, const ut8 *buf, int count) {
	if (!fd || !buf || count < 0 || !fd->data) {
		return -1;
	}
	RBuffer *b = fd->data;
	return r_buf_write (b, buf, count);
}