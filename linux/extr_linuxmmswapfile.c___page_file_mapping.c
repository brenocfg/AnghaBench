#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct page {int dummy; } ;
struct address_space {int dummy; } ;
struct TYPE_4__ {TYPE_1__* swap_file; } ;
struct TYPE_3__ {struct address_space* f_mapping; } ;

/* Variables and functions */
 TYPE_2__* page_swap_info (struct page*) ; 

struct address_space *__page_file_mapping(struct page *page)
{
	return page_swap_info(page)->swap_file->f_mapping;
}