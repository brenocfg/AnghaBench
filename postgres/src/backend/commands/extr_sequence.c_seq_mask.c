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
typedef  int /*<<< orphan*/  BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  mask_page_lsn_and_checksum (char*) ; 
 int /*<<< orphan*/  mask_unused_space (char*) ; 

void
seq_mask(char *page, BlockNumber blkno)
{
	mask_page_lsn_and_checksum(page);

	mask_unused_space(page);
}