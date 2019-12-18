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
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct page** kvmalloc_array (size_t,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct page **get_pages_array(size_t n)
{
	return kvmalloc_array(n, sizeof(struct page *), GFP_KERNEL);
}