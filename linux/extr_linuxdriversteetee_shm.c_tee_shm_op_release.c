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
struct tee_shm {int dummy; } ;
struct dma_buf {struct tee_shm* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  tee_shm_release (struct tee_shm*) ; 

__attribute__((used)) static void tee_shm_op_release(struct dma_buf *dmabuf)
{
	struct tee_shm *shm = dmabuf->priv;

	tee_shm_release(shm);
}