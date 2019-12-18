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
struct ocfs2_refcount_rec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  swap (struct ocfs2_refcount_rec,struct ocfs2_refcount_rec) ; 

__attribute__((used)) static void swap_refcount_rec(void *a, void *b, int size)
{
	struct ocfs2_refcount_rec *l = a, *r = b;

	swap(*l, *r);
}