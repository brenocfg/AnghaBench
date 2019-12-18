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
struct snd_pcm_substream {TYPE_1__* runtime; } ;
struct idma_ctrl {void (* cb ) (void*,int) ;int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {struct idma_ctrl* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void idma_setcallbk(struct snd_pcm_substream *substream,
				void (*cb)(void *, int))
{
	struct idma_ctrl *prtd = substream->runtime->private_data;

	spin_lock(&prtd->lock);
	prtd->cb = cb;
	spin_unlock(&prtd->lock);
}