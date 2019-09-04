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
struct xenvif_queue {scalar_t__ dealloc_cons; scalar_t__ dealloc_prod; } ;

/* Variables and functions */

__attribute__((used)) static inline bool tx_dealloc_work_todo(struct xenvif_queue *queue)
{
	return queue->dealloc_cons != queue->dealloc_prod;
}