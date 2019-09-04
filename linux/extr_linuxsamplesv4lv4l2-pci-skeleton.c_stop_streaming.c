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
struct vb2_queue {int dummy; } ;
struct skeleton {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VB2_BUF_STATE_ERROR ; 
 int /*<<< orphan*/  return_all_buffers (struct skeleton*,int /*<<< orphan*/ ) ; 
 struct skeleton* vb2_get_drv_priv (struct vb2_queue*) ; 

__attribute__((used)) static void stop_streaming(struct vb2_queue *vq)
{
	struct skeleton *skel = vb2_get_drv_priv(vq);

	/* TODO: stop DMA */

	/* Release all active buffers */
	return_all_buffers(skel, VB2_BUF_STATE_ERROR);
}