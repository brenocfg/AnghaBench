#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct nvm_addrf_12 {int /*<<< orphan*/  sec_len; int /*<<< orphan*/  sec_offset; int /*<<< orphan*/  pg_len; int /*<<< orphan*/  pg_offset; int /*<<< orphan*/  blk_len; int /*<<< orphan*/  blk_offset; int /*<<< orphan*/  pln_len; int /*<<< orphan*/  pln_offset; int /*<<< orphan*/  lun_len; int /*<<< orphan*/  lun_offset; int /*<<< orphan*/  ch_len; int /*<<< orphan*/  ch_offset; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  scnprintf (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t nvm_dev_attr_show_ppaf(struct nvm_addrf_12 *ppaf, char *page)
{
	return scnprintf(page, PAGE_SIZE,
		"0x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x\n",
				ppaf->ch_offset, ppaf->ch_len,
				ppaf->lun_offset, ppaf->lun_len,
				ppaf->pln_offset, ppaf->pln_len,
				ppaf->blk_offset, ppaf->blk_len,
				ppaf->pg_offset, ppaf->pg_len,
				ppaf->sec_offset, ppaf->sec_len);
}