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
struct ct_vm {int /*<<< orphan*/  (* unmap ) (struct ct_vm*,int /*<<< orphan*/ *) ;} ;
struct ct_atc_pcm {int /*<<< orphan*/ * vm_block; } ;
struct ct_atc {struct ct_vm* vm; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct ct_vm*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ct_unmap_audio_buffer(struct ct_atc *atc, struct ct_atc_pcm *apcm)
{
	struct ct_vm *vm;

	if (!apcm->vm_block)
		return;

	vm = atc->vm;

	vm->unmap(vm, apcm->vm_block);

	apcm->vm_block = NULL;
}