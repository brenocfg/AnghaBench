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
struct stable_node {int dummy; } ;
struct page {int dummy; } ;

/* Variables and functions */
 scalar_t__ PageKsm (struct page*) ; 
 struct stable_node* page_rmapping (struct page*) ; 

__attribute__((used)) static inline struct stable_node *page_stable_node(struct page *page)
{
	return PageKsm(page) ? page_rmapping(page) : NULL;
}