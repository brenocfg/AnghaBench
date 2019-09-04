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
struct pcpu_chunk {int dummy; } ;
struct page {unsigned long index; } ;

/* Variables and functions */

__attribute__((used)) static void pcpu_set_page_chunk(struct page *page, struct pcpu_chunk *pcpu)
{
	page->index = (unsigned long)pcpu;
}