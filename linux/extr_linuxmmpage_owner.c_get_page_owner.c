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
typedef  void page_owner ;
struct page_ext {int dummy; } ;
struct TYPE_2__ {int offset; } ;

/* Variables and functions */
 TYPE_1__ page_owner_ops ; 

__attribute__((used)) static inline struct page_owner *get_page_owner(struct page_ext *page_ext)
{
	return (void *)page_ext + page_owner_ops.offset;
}