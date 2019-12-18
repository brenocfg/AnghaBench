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
 int /*<<< orphan*/  PageWaiters (struct page*) ; 
 int /*<<< orphan*/  wake_up_page_bit (struct page*,int) ; 

__attribute__((used)) static void wake_up_page(struct page *page, int bit)
{
	if (!PageWaiters(page))
		return;
	wake_up_page_bit(page, bit);
}