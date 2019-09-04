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
struct mbox_out {int dummy; } ;
typedef  int /*<<< orphan*/  raw_mbox ;
struct TYPE_2__ {int /*<<< orphan*/  m_out; } ;
typedef  TYPE_1__ mbox_t ;
typedef  int /*<<< orphan*/  adapter_t ;

/* Variables and functions */
 unsigned char FC_DEL_LOGDRV ; 
 unsigned char OP_SUP_DEL_LOGDRV ; 
 int issue_scb_block (int /*<<< orphan*/ *,unsigned char*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
mega_support_random_del(adapter_t *adapter)
{
	unsigned char raw_mbox[sizeof(struct mbox_out)];
	mbox_t *mbox;
	int rval;

	mbox = (mbox_t *)raw_mbox;

	memset(&mbox->m_out, 0, sizeof(raw_mbox));

	/*
	 * issue command
	 */
	raw_mbox[0] = FC_DEL_LOGDRV;
	raw_mbox[2] = OP_SUP_DEL_LOGDRV;

	rval = issue_scb_block(adapter, raw_mbox);

	return !rval;
}