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
struct usX2Ydev {int chip_status; int /*<<< orphan*/  us428ctls_wait_queue_head; struct us428ctls_sharedmem* us428ctls_sharedmem; } ;
struct us428ctls_sharedmem {scalar_t__ CtlSnapShotLast; scalar_t__ CtlSnapShotRed; } ;
struct snd_hwdep {struct usX2Ydev* private_data; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int /*<<< orphan*/  __poll_t ;

/* Variables and functions */
 int /*<<< orphan*/  EPOLLHUP ; 
 int /*<<< orphan*/  EPOLLIN ; 
 int USX2Y_STAT_CHIP_HUP ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static __poll_t snd_us428ctls_poll(struct snd_hwdep *hw, struct file *file, poll_table *wait)
{
	__poll_t	mask = 0;
	struct usX2Ydev	*us428 = hw->private_data;
	struct us428ctls_sharedmem *shm = us428->us428ctls_sharedmem;
	if (us428->chip_status & USX2Y_STAT_CHIP_HUP)
		return EPOLLHUP;

	poll_wait(file, &us428->us428ctls_wait_queue_head, wait);

	if (shm != NULL && shm->CtlSnapShotLast != shm->CtlSnapShotRed)
		mask |= EPOLLIN;

	return mask;
}