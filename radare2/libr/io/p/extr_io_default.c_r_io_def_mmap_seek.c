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
typedef  int /*<<< orphan*/  ut64 ;
struct TYPE_6__ {int /*<<< orphan*/  off; } ;
struct TYPE_5__ {int /*<<< orphan*/  buf; int /*<<< orphan*/  fd; scalar_t__ rawio; } ;
typedef  TYPE_1__ RIOMMapFileObj ;
typedef  TYPE_2__ RIO ;

/* Variables and functions */
 int /*<<< orphan*/  UT64_MAX ; 
 int /*<<< orphan*/  lseek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r_buf_seek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ut64 r_io_def_mmap_seek(RIO *io, RIOMMapFileObj *mmo, ut64 offset, int whence) {
	if (!mmo) {
		return UT64_MAX;
	}
	if (mmo->rawio) {
		io->off = lseek (mmo->fd, offset, whence);
		return io->off;
	}
	if (!mmo->buf) {
		return UT64_MAX;
	}
	io->off = r_buf_seek (mmo->buf, offset, whence);
	return io->off;
}