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
 int /*<<< orphan*/  trace_page_ref_mod_and_test (struct page*,int,int) ; 

void __page_ref_mod_and_test(struct page *page, int v, int ret)
{
	trace_page_ref_mod_and_test(page, v, ret);
}