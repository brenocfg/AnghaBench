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
struct page {scalar_t__ index; } ;
struct ecryptfs_crypt_stat {int dummy; } ;
typedef  int loff_t ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int ecryptfs_lower_header_size (struct ecryptfs_crypt_stat*) ; 

__attribute__((used)) static loff_t lower_offset_for_page(struct ecryptfs_crypt_stat *crypt_stat,
				    struct page *page)
{
	return ecryptfs_lower_header_size(crypt_stat) +
	       ((loff_t)page->index << PAGE_SHIFT);
}