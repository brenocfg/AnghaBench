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
struct snd_pcm_substream {int /*<<< orphan*/  runtime; } ;
struct dw_i2s_dev {unsigned int (* tx_fn ) (struct dw_i2s_dev*,int /*<<< orphan*/ ,unsigned int,int*) ;unsigned int (* rx_fn ) (struct dw_i2s_dev*,int /*<<< orphan*/ ,unsigned int,int*) ;int /*<<< orphan*/  rx_ptr; int /*<<< orphan*/  tx_ptr; int /*<<< orphan*/  rx_substream; int /*<<< orphan*/  tx_substream; } ;

/* Variables and functions */
 unsigned int READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmpxchg (int /*<<< orphan*/ *,unsigned int,unsigned int) ; 
 struct snd_pcm_substream* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  snd_pcm_period_elapsed (struct snd_pcm_substream*) ; 
 scalar_t__ snd_pcm_running (struct snd_pcm_substream*) ; 
 unsigned int stub1 (struct dw_i2s_dev*,int /*<<< orphan*/ ,unsigned int,int*) ; 
 unsigned int stub2 (struct dw_i2s_dev*,int /*<<< orphan*/ ,unsigned int,int*) ; 

__attribute__((used)) static void dw_pcm_transfer(struct dw_i2s_dev *dev, bool push)
{
	struct snd_pcm_substream *substream;
	bool active, period_elapsed;

	rcu_read_lock();
	if (push)
		substream = rcu_dereference(dev->tx_substream);
	else
		substream = rcu_dereference(dev->rx_substream);
	active = substream && snd_pcm_running(substream);
	if (active) {
		unsigned int ptr;
		unsigned int new_ptr;

		if (push) {
			ptr = READ_ONCE(dev->tx_ptr);
			new_ptr = dev->tx_fn(dev, substream->runtime, ptr,
					&period_elapsed);
			cmpxchg(&dev->tx_ptr, ptr, new_ptr);
		} else {
			ptr = READ_ONCE(dev->rx_ptr);
			new_ptr = dev->rx_fn(dev, substream->runtime, ptr,
					&period_elapsed);
			cmpxchg(&dev->rx_ptr, ptr, new_ptr);
		}

		if (period_elapsed)
			snd_pcm_period_elapsed(substream);
	}
	rcu_read_unlock();
}