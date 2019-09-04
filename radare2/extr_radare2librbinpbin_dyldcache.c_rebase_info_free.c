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
typedef  int ut8 ;
struct TYPE_4__ {int version; struct TYPE_4__* one_page_buf; } ;
typedef  int /*<<< orphan*/  RDyldRebaseInfo3 ;
typedef  int /*<<< orphan*/  RDyldRebaseInfo2 ;
typedef  int /*<<< orphan*/  RDyldRebaseInfo1 ;
typedef  TYPE_1__ RDyldRebaseInfo ;

/* Variables and functions */
 int /*<<< orphan*/  R_FREE (TYPE_1__*) ; 
 int /*<<< orphan*/  rebase_info1_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rebase_info2_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rebase_info3_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rebase_info_free(RDyldRebaseInfo *rebase_info) {
	if (!rebase_info) {
		return;
	}

	R_FREE (rebase_info->one_page_buf);

	ut8 version = rebase_info->version;

	if (version == 1) {
		rebase_info1_free ((RDyldRebaseInfo1*) rebase_info);
	} else if (version == 2) {
		rebase_info2_free ((RDyldRebaseInfo2*) rebase_info);
	} else if (version == 3) {
		rebase_info3_free ((RDyldRebaseInfo3*) rebase_info);
	} else {
		R_FREE (rebase_info);
	}
}