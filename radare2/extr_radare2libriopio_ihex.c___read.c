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
typedef  int /*<<< orphan*/  ut8 ;
struct TYPE_8__ {int /*<<< orphan*/  off; int /*<<< orphan*/  Oxff; } ;
struct TYPE_7__ {TYPE_1__* data; } ;
struct TYPE_6__ {int /*<<< orphan*/  rbuf; } ;
typedef  TYPE_1__ Rihex ;
typedef  TYPE_2__ RIODesc ;
typedef  TYPE_3__ RIO ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int r_buf_read_at (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int __read(RIO *io, RIODesc *fd, ut8 *buf, int count) {
	if (!fd || !fd->data || (count <= 0)) {
		return -1;
	}
	Rihex *rih = fd->data;
	memset (buf, io->Oxff, count);
	return r_buf_read_at (rih->rbuf, io->off, buf, count);
}