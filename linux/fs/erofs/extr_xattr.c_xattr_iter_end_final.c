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
struct xattr_iter {int /*<<< orphan*/  page; } ;

/* Variables and functions */
 int /*<<< orphan*/  xattr_iter_end (struct xattr_iter*,int) ; 

__attribute__((used)) static inline void xattr_iter_end_final(struct xattr_iter *it)
{
	if (!it->page)
		return;

	xattr_iter_end(it, true);
}