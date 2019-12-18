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
typedef  int /*<<< orphan*/  st64 ;
typedef  int /*<<< orphan*/  st32 ;
struct TYPE_3__ {int /*<<< orphan*/  tid; int /*<<< orphan*/  pid; } ;
typedef  TYPE_1__ ptid_t ;

/* Variables and functions */

ptid_t ptid_build (st32 pid, st64 tid) {
	ptid_t ptid;
	ptid.pid = pid;
	ptid.tid = tid;

	return ptid;
}