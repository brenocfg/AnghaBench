#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct splice_pipe_desc {int nr_pages; TYPE_1__* partial; struct page** pages; } ;
struct page {int dummy; } ;
struct TYPE_2__ {unsigned int offset; unsigned int len; } ;

/* Variables and functions */

__attribute__((used)) static bool spd_can_coalesce(const struct splice_pipe_desc *spd,
			     struct page *page,
			     unsigned int offset)
{
	return	spd->nr_pages &&
		spd->pages[spd->nr_pages - 1] == page &&
		(spd->partial[spd->nr_pages - 1].offset +
		 spd->partial[spd->nr_pages - 1].len == offset);
}