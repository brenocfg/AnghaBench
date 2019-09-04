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
struct kvm_segment {int unusable; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct kvm_segment*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void kvm_seg_set_unusable(struct kvm_segment *segp)
{
	memset(segp, 0, sizeof(*segp));
	segp->unusable = true;
}