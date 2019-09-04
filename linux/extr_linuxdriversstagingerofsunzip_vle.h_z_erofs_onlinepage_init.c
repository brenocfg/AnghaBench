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
typedef  int /*<<< orphan*/  z_erofs_onlinepage_t ;
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATOMIC_INIT (int) ; 
 int /*<<< orphan*/  SetPagePrivate (struct page*) ; 
 int /*<<< orphan*/  set_page_private (struct page*,unsigned long) ; 
 int /*<<< orphan*/  smp_wmb () ; 

__attribute__((used)) static inline void z_erofs_onlinepage_init(struct page *page)
{
	union {
		z_erofs_onlinepage_t o;
		unsigned long v;
	/* keep from being unlocked in advance */
	} u = { .o = ATOMIC_INIT(1) };

	set_page_private(page, u.v);
	smp_wmb();
	SetPagePrivate(page);
}