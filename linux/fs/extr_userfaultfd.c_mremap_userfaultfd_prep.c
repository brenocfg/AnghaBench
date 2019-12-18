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
struct vm_userfaultfd_ctx {struct userfaultfd_ctx* ctx; } ;
struct TYPE_2__ {struct userfaultfd_ctx* ctx; } ;
struct vm_area_struct {int vm_flags; TYPE_1__ vm_userfaultfd_ctx; } ;
struct userfaultfd_ctx {int features; int /*<<< orphan*/  mmap_changing; } ;

/* Variables and functions */
 TYPE_1__ NULL_VM_UFFD_CTX ; 
 int UFFD_FEATURE_EVENT_REMAP ; 
 int VM_UFFD_MISSING ; 
 int VM_UFFD_WP ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  userfaultfd_ctx_get (struct userfaultfd_ctx*) ; 

void mremap_userfaultfd_prep(struct vm_area_struct *vma,
			     struct vm_userfaultfd_ctx *vm_ctx)
{
	struct userfaultfd_ctx *ctx;

	ctx = vma->vm_userfaultfd_ctx.ctx;

	if (!ctx)
		return;

	if (ctx->features & UFFD_FEATURE_EVENT_REMAP) {
		vm_ctx->ctx = ctx;
		userfaultfd_ctx_get(ctx);
		WRITE_ONCE(ctx->mmap_changing, true);
	} else {
		/* Drop uffd context if remap feature not enabled */
		vma->vm_userfaultfd_ctx = NULL_VM_UFFD_CTX;
		vma->vm_flags &= ~(VM_UFFD_WP | VM_UFFD_MISSING);
	}
}