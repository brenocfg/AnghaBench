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
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  isofs_get_block ; 
 int mpage_readpage (struct page*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int isofs_readpage(struct file *file, struct page *page)
{
	return mpage_readpage(page, isofs_get_block);
}