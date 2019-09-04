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
 int issue_scb_block (int /*<<< orphan*/ *,unsigned char*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
mega_support_ext_cdb(adapter_t *adapter)
{
	unsigned char raw_mbox[sizeof(struct mbox_out)];
	mbox_t *mbox;
	int rval;

	mbox = (mbox_t *)raw_mbox;

	memset(&mbox->m_out, 0, sizeof(raw_mbox));
	/*
	 * issue command to find out if controller supports extended CDBs.
	 */
	raw_mbox[0] = 0xA4;
	raw_mbox[2] = 0x16;

	rval = issue_scb_block(adapter, raw_mbox);

	return !rval;
}