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
typedef  int /*<<< orphan*/  ut64 ;
struct TYPE_5__ {int /*<<< orphan*/  data; } ;
struct TYPE_4__ {int /*<<< orphan*/  off; } ;
typedef  int /*<<< orphan*/  RIODesc ;
typedef  TYPE_1__ RIO ;

/* Variables and functions */
 int debug_gdb_read_at (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 TYPE_2__* desc ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int __read(RIO *io, RIODesc *fd, ut8 *buf, int count) {
	if (!io || !fd || !buf || count < 1) {
		return -1;
	}
	memset (buf, 0xff, count);
	ut64 addr = io->off;
	if (!desc || !desc->data) {
		return -1;
	}
	return debug_gdb_read_at (buf, count, addr);
}