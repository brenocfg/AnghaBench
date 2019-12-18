#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut64 ;
struct TYPE_4__ {int /*<<< orphan*/ * buf; int /*<<< orphan*/  flags; int /*<<< orphan*/  filename; int /*<<< orphan*/ * io_backref; } ;
typedef  TYPE_1__ RIOMMapFileObj ;
typedef  int /*<<< orphan*/  RIO ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  r_buf_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * r_buf_new_mmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_buf_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_io_mmap_seek (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool r_io_mmap_refresh_buf(RIOMMapFileObj *mmo) {
	RIO* io = mmo->io_backref;
	ut64 cur = mmo->buf? r_buf_tell (mmo->buf): 0;
	if (mmo->buf) {
		r_buf_free (mmo->buf);
		mmo->buf = NULL;
	}
	mmo->buf = r_buf_new_mmap (mmo->filename, mmo->flags);
	if (mmo->buf) {
		r_io_mmap_seek (io, mmo, cur, SEEK_SET);
	}
	return mmo->buf != NULL;
}