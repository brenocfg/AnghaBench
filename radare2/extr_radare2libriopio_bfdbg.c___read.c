#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
struct TYPE_14__ {int base; int screen; int screen_size; int input; int input_size; scalar_t__ input_buf; scalar_t__ screen_buf; scalar_t__ mem; } ;
struct TYPE_13__ {int off; } ;
struct TYPE_12__ {TYPE_4__* bfvm; } ;
struct TYPE_11__ {TYPE_2__* data; } ;
typedef  TYPE_1__ RIODesc ;
typedef  TYPE_2__ RIOBfdbg ;
typedef  TYPE_3__ RIO ;

/* Variables and functions */
 scalar_t__ RIOBFDBG_BUF (TYPE_1__*) ; 
 int RIOBFDBG_SZ (TYPE_1__*) ; 
 scalar_t__ is_in_base (int,TYPE_4__*) ; 
 scalar_t__ is_in_input (int,TYPE_4__*) ; 
 scalar_t__ is_in_screen (int,TYPE_4__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__,int) ; 

__attribute__((used)) static int __read(RIO *io, RIODesc *fd, ut8 *buf, int count) {
	RIOBfdbg *riom;
	int sz;
	if (!fd || !fd->data) {
		return -1;
	}
	riom = fd->data;
	/* data base buffer */
	if (is_in_base (io->off, riom->bfvm)) {
		int n = io->off-riom->bfvm->base;
		if (n > count) {
			count = n;
		}
		memcpy (buf, riom->bfvm->mem+n, count);
		return count;
	}
	/* screen buffer */
	if (is_in_screen (io->off, riom->bfvm)) {
		int n = io->off-riom->bfvm->screen;
		if (n > count) {
			count = riom->bfvm->screen_size - n;
		}
		memcpy (buf, riom->bfvm->screen_buf+n, count);
		return count;
	}
	/* input buffer */
	if (is_in_input (io->off, riom->bfvm)) {
		int n = io->off-riom->bfvm->input;
		if (n > count) {
			count = riom->bfvm->input_size - n;
		}
		memcpy (buf, riom->bfvm->input_buf+n, count);
		return count;
	}
	/* read from file */
	sz = RIOBFDBG_SZ (fd);
	if (io->off + count >= sz) {
		count = sz - io->off;
	}
	if (io->off >= sz) {
		return -1;
	}
	memcpy (buf, RIOBFDBG_BUF (fd)+io->off, count);
	return count;
}