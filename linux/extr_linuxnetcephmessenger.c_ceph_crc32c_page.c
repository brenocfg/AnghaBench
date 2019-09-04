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
typedef  int /*<<< orphan*/  u32 ;
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crc32c (int /*<<< orphan*/ ,char*,unsigned int) ; 
 char* kmap (struct page*) ; 
 int /*<<< orphan*/  kunmap (struct page*) ; 

__attribute__((used)) static u32 ceph_crc32c_page(u32 crc, struct page *page,
				unsigned int page_offset,
				unsigned int length)
{
	char *kaddr;

	kaddr = kmap(page);
	BUG_ON(kaddr == NULL);
	crc = crc32c(crc, kaddr + page_offset, length);
	kunmap(page);

	return crc;
}