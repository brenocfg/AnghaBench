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
struct inode {int dummy; } ;
struct file {struct channel_data* private_data; } ;
struct cosa_data {int nchannels; int /*<<< orphan*/  lock; int /*<<< orphan*/  usage; struct channel_data* chan; } ;
struct channel_data {scalar_t__ usage; int /*<<< orphan*/  rx_done; int /*<<< orphan*/  setup_rx; int /*<<< orphan*/  tx_done; } ;

/* Variables and functions */
 int CARD_MINOR_BITS ; 
 int EBUSY ; 
 int ENODEV ; 
 int /*<<< orphan*/  chrdev_rx_done ; 
 int /*<<< orphan*/  chrdev_setup_rx ; 
 int /*<<< orphan*/  chrdev_tx_done ; 
 struct cosa_data* cosa_cards ; 
 int /*<<< orphan*/  cosa_chardev_mutex ; 
 int /*<<< orphan*/  file_inode (struct file*) ; 
 int iminor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int nr_cards ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int cosa_open(struct inode *inode, struct file *file)
{
	struct cosa_data *cosa;
	struct channel_data *chan;
	unsigned long flags;
	int n;
	int ret = 0;

	mutex_lock(&cosa_chardev_mutex);
	if ((n=iminor(file_inode(file))>>CARD_MINOR_BITS)
		>= nr_cards) {
		ret = -ENODEV;
		goto out;
	}
	cosa = cosa_cards+n;

	if ((n=iminor(file_inode(file))
		& ((1<<CARD_MINOR_BITS)-1)) >= cosa->nchannels) {
		ret = -ENODEV;
		goto out;
	}
	chan = cosa->chan + n;
	
	file->private_data = chan;

	spin_lock_irqsave(&cosa->lock, flags);

	if (chan->usage < 0) { /* in netdev mode */
		spin_unlock_irqrestore(&cosa->lock, flags);
		ret = -EBUSY;
		goto out;
	}
	cosa->usage++;
	chan->usage++;

	chan->tx_done = chrdev_tx_done;
	chan->setup_rx = chrdev_setup_rx;
	chan->rx_done = chrdev_rx_done;
	spin_unlock_irqrestore(&cosa->lock, flags);
out:
	mutex_unlock(&cosa_chardev_mutex);
	return ret;
}