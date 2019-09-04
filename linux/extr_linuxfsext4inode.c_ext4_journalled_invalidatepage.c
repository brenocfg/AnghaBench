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
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ __ext4_journalled_invalidatepage (struct page*,unsigned int,unsigned int) ; 

__attribute__((used)) static void ext4_journalled_invalidatepage(struct page *page,
					   unsigned int offset,
					   unsigned int length)
{
	WARN_ON(__ext4_journalled_invalidatepage(page, offset, length) < 0);
}