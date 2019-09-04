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
struct metapage {int dummy; } ;

/* Variables and functions */
 scalar_t__ PagePrivate (struct page*) ; 
 scalar_t__ page_private (struct page*) ; 

__attribute__((used)) static inline struct metapage *page_to_mp(struct page *page, int offset)
{
	return PagePrivate(page) ? (struct metapage *)page_private(page) : NULL;
}