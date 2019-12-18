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
typedef  int /*<<< orphan*/  ut8 ;
typedef  int /*<<< orphan*/  ut64 ;
struct TYPE_3__ {int version; } ;
typedef  int /*<<< orphan*/  RDyldRebaseInfo3 ;
typedef  int /*<<< orphan*/  RDyldRebaseInfo2 ;
typedef  int /*<<< orphan*/  RDyldRebaseInfo1 ;
typedef  TYPE_1__ RDyldRebaseInfo ;

/* Variables and functions */
 int /*<<< orphan*/  rebase_bytes_v1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rebase_bytes_v2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rebase_bytes_v3 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rebase_bytes(RDyldRebaseInfo *rebase_info, ut8 *buf, ut64 offset, int count, ut64 start_of_write) {
	if (!rebase_info || !buf) {
		return;
	}

	if (rebase_info->version == 3) {
		rebase_bytes_v3 ((RDyldRebaseInfo3*) rebase_info, buf, offset, count, start_of_write);
	} else if (rebase_info->version == 2) {
		rebase_bytes_v2 ((RDyldRebaseInfo2*) rebase_info, buf, offset, count, start_of_write);
	} else if (rebase_info->version == 1) {
		rebase_bytes_v1 ((RDyldRebaseInfo1*) rebase_info, buf, offset, count, start_of_write);
	}
}