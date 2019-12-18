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
typedef  int /*<<< orphan*/  buf ;
struct TYPE_5__ {TYPE_1__* core; } ;
struct TYPE_4__ {int /*<<< orphan*/  io; } ;
typedef  TYPE_2__ RCoreObjc ;

/* Variables and functions */
 int /*<<< orphan*/  r_io_read_at (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  r_read_le64 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ut64 readQword (RCoreObjc *objc, ut64 addr) {
	ut8 buf[8];
	(void)r_io_read_at (objc->core->io, addr, buf, sizeof (buf));
	return r_read_le64 (buf);
}