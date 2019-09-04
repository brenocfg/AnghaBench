#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
typedef  int /*<<< orphan*/  ut64 ;
struct TYPE_5__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ RIODesc ;
typedef  int /*<<< orphan*/  RIO ;
typedef  int /*<<< orphan*/  RBuffer ;

/* Variables and functions */
 int /*<<< orphan*/ * RIOSPARSE_BUF (TYPE_1__*) ; 
 int /*<<< orphan*/  RIOSPARSE_OFF (TYPE_1__*) ; 
 int /*<<< orphan*/  r_buf_read_at (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int __read(RIO *io, RIODesc *fd, ut8 *buf, int count) {
	ut64 o;
	RBuffer *b;
	if (!fd || !fd->data) {
		return -1;
	}
	b = RIOSPARSE_BUF(fd);
	o = RIOSPARSE_OFF(fd);
	(void)r_buf_read_at (b, o, buf, count);
	return count;
}