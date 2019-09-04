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
typedef  int /*<<< orphan*/  ut64 ;
struct TYPE_6__ {int /*<<< orphan*/  off; } ;
struct TYPE_5__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ RIODesc ;
typedef  TYPE_2__ RIO ;

/* Variables and functions */
 scalar_t__ windbg_get_target (int /*<<< orphan*/ ) ; 
 int windbg_read_at (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int windbg_read_at_phys (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  windbg_va_to_pa (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __read(RIO *io, RIODesc *fd, ut8 *buf, int count) {
	if (!fd) {
		return -1;
	}

	if (windbg_get_target (fd->data)) {
		ut64 va;
		if (!windbg_va_to_pa (fd->data, io->off, &va)) {
			return -1;
		}
		return windbg_read_at_phys (fd->data, buf, va, count);
	}

	return windbg_read_at (fd->data, buf, io->off, count);
}