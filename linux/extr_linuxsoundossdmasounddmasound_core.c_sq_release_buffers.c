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
struct sound_queue {int numBufs; int /*<<< orphan*/ * buffers; int /*<<< orphan*/  bufSize; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* dma_free ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {TYPE_1__ mach; } ;

/* Variables and functions */
 TYPE_2__ dmasound ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sq_release_buffers(struct sound_queue *sq)
{
	int i;

	if (sq->buffers) {
		for (i = 0; i < sq->numBufs; i++)
			dmasound.mach.dma_free(sq->buffers[i], sq->bufSize);
		kfree(sq->buffers);
		sq->buffers = NULL;
	}
}