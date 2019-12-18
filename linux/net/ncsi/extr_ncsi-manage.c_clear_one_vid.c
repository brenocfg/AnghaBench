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
typedef  scalar_t__ u16 ;
struct ncsi_dev_priv {int dummy; } ;
struct ncsi_cmd_arg {int* bytes; scalar_t__* words; int /*<<< orphan*/  type; } ;
struct ncsi_channel_vlan_filter {int n_vids; scalar_t__* vids; int /*<<< orphan*/  bitmap; } ;
struct ncsi_channel {int /*<<< orphan*/  lock; struct ncsi_channel_vlan_filter vlan_filter; } ;

/* Variables and functions */
 int /*<<< orphan*/  NCSI_PKT_CMD_SVF ; 
 int /*<<< orphan*/  clear_bit (int,void*) ; 
 int find_next_bit (void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int clear_one_vid(struct ncsi_dev_priv *ndp, struct ncsi_channel *nc,
			 struct ncsi_cmd_arg *nca)
{
	struct ncsi_channel_vlan_filter *ncf;
	unsigned long flags;
	void *bitmap;
	int index;
	u16 vid;

	ncf = &nc->vlan_filter;
	bitmap = &ncf->bitmap;

	spin_lock_irqsave(&nc->lock, flags);
	index = find_next_bit(bitmap, ncf->n_vids, 0);
	if (index >= ncf->n_vids) {
		spin_unlock_irqrestore(&nc->lock, flags);
		return -1;
	}
	vid = ncf->vids[index];

	clear_bit(index, bitmap);
	ncf->vids[index] = 0;
	spin_unlock_irqrestore(&nc->lock, flags);

	nca->type = NCSI_PKT_CMD_SVF;
	nca->words[1] = vid;
	/* HW filter index starts at 1 */
	nca->bytes[6] = index + 1;
	nca->bytes[7] = 0x00;
	return 0;
}