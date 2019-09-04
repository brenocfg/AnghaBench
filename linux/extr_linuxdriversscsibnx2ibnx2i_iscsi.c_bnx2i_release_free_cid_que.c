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
struct TYPE_2__ {int /*<<< orphan*/ * conn_cid_tbl; int /*<<< orphan*/ * cid_que_base; } ;
struct bnx2i_hba {TYPE_1__ cid_que; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bnx2i_release_free_cid_que(struct bnx2i_hba *hba)
{
	kfree(hba->cid_que.cid_que_base);
	hba->cid_que.cid_que_base = NULL;

	kfree(hba->cid_que.conn_cid_tbl);
	hba->cid_que.conn_cid_tbl = NULL;
}