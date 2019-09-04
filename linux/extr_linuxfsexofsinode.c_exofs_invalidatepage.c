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
struct page {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXOFS_DBGMSG (char*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 

__attribute__((used)) static void exofs_invalidatepage(struct page *page, unsigned int offset,
				 unsigned int length)
{
	EXOFS_DBGMSG("page 0x%lx offset 0x%x length 0x%x\n",
		     page->index, offset, length);
	WARN_ON(1);
}