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
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ClearPageMappedToDisk (struct page*) ; 
 int /*<<< orphan*/  ClearPageUptodate (struct page*) ; 
 int /*<<< orphan*/  GOSSIP_INODE_DEBUG ; 
 int /*<<< orphan*/  gossip_debug (int /*<<< orphan*/ ,char*,struct page*,unsigned int) ; 

__attribute__((used)) static void orangefs_invalidatepage(struct page *page,
				 unsigned int offset,
				 unsigned int length)
{
	gossip_debug(GOSSIP_INODE_DEBUG,
		     "orangefs_invalidatepage called on page %p "
		     "(offset is %u)\n",
		     page,
		     offset);

	ClearPageUptodate(page);
	ClearPageMappedToDisk(page);
	return;

}