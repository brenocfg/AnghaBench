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
struct vm_area_struct {int dummy; } ;
struct userfaultfd_ctx {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline bool userfaultfd_huge_must_wait(struct userfaultfd_ctx *ctx,
					 struct vm_area_struct *vma,
					 unsigned long address,
					 unsigned long flags,
					 unsigned long reason)
{
	return false;	/* should never get here */
}