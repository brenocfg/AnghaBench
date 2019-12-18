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
struct nfs_page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PagePrivate (struct page*) ; 
 scalar_t__ page_private (struct page*) ; 

__attribute__((used)) static struct nfs_page *
nfs_page_private_request(struct page *page)
{
	if (!PagePrivate(page))
		return NULL;
	return (struct nfs_page *)page_private(page);
}