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
struct sound_queue {int numBufs; int bufSize; int /*<<< orphan*/ * buffers; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* dma_free ) (int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* dma_alloc ) (int,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {TYPE_1__ mach; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_2__ dmasound ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc_array (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sq_allocate_buffers(struct sound_queue *sq, int num, int size)
{
	int i;

	if (sq->buffers)
		return 0;
	sq->numBufs = num;
	sq->bufSize = size;
	sq->buffers = kmalloc_array (num, sizeof(char *), GFP_KERNEL);
	if (!sq->buffers)
		return -ENOMEM;
	for (i = 0; i < num; i++) {
		sq->buffers[i] = dmasound.mach.dma_alloc(size, GFP_KERNEL);
		if (!sq->buffers[i]) {
			while (i--)
				dmasound.mach.dma_free(sq->buffers[i], size);
			kfree(sq->buffers);
			sq->buffers = NULL;
			return -ENOMEM;
		}
	}
	return 0;
}