#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
typedef  int /*<<< orphan*/  ut64 ;
struct TYPE_2__ {int /*<<< orphan*/  io; } ;
struct r_anal_t {TYPE_1__ iob; } ;

/* Variables and functions */
 int r_io_read_at (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static bool r_core_anal_read_at(struct r_anal_t *anal, ut64 addr, ut8 *buf, int len) {
	return r_io_read_at (anal->iob.io, addr, buf, len);
}