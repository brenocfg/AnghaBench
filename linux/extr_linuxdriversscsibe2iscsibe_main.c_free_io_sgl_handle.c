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
struct sgl_handle {int dummy; } ;
struct TYPE_2__ {int ios_per_ctrl; } ;
struct beiscsi_hba {size_t io_sgl_free_index; int /*<<< orphan*/  io_sgl_lock; TYPE_1__ params; int /*<<< orphan*/  io_sgl_hndl_avbl; struct sgl_handle** io_sgl_hndl_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEISCSI_LOG_IO ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  beiscsi_log (struct beiscsi_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t,...) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
free_io_sgl_handle(struct beiscsi_hba *phba, struct sgl_handle *psgl_handle)
{
	unsigned long flags;

	spin_lock_irqsave(&phba->io_sgl_lock, flags);
	beiscsi_log(phba, KERN_INFO, BEISCSI_LOG_IO,
		    "BM_%d : In free_,io_sgl_free_index=%d\n",
		    phba->io_sgl_free_index);

	if (phba->io_sgl_hndl_base[phba->io_sgl_free_index]) {
		/*
		 * this can happen if clean_task is called on a task that
		 * failed in xmit_task or alloc_pdu.
		 */
		beiscsi_log(phba, KERN_INFO, BEISCSI_LOG_IO,
			    "BM_%d : Double Free in IO SGL io_sgl_free_index=%d, value there=%p\n",
			    phba->io_sgl_free_index,
			    phba->io_sgl_hndl_base[phba->io_sgl_free_index]);
		spin_unlock_irqrestore(&phba->io_sgl_lock, flags);
		return;
	}
	phba->io_sgl_hndl_base[phba->io_sgl_free_index] = psgl_handle;
	phba->io_sgl_hndl_avbl++;
	if (phba->io_sgl_free_index == (phba->params.ios_per_ctrl - 1))
		phba->io_sgl_free_index = 0;
	else
		phba->io_sgl_free_index++;
	spin_unlock_irqrestore(&phba->io_sgl_lock, flags);
}