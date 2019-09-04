#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int size; } ;
struct TYPE_4__ {int vaddr; TYPE_1__ text_range; } ;
typedef  TYPE_2__ RKext ;

/* Variables and functions */

__attribute__((used)) static int kexts_sort_vaddr_func(const void *a, const void *b) {
	RKext *A = (RKext *) a;
	RKext *B = (RKext *) b;
	int vaddr_compare = A->vaddr - B->vaddr;
	if (vaddr_compare == 0) {
		return A->text_range.size - B->text_range.size;
	}
	return vaddr_compare;
}