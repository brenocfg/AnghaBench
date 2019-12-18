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
struct batadv_priv {int dummy; } ;
struct batadv_orig_node {int /*<<< orphan*/  tt_buff_lock; scalar_t__ tt_buff_len; scalar_t__ tt_buff; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 scalar_t__ kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,void const*,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void batadv_tt_save_orig_buffer(struct batadv_priv *bat_priv,
				       struct batadv_orig_node *orig_node,
				       const void *tt_buff,
				       u16 tt_buff_len)
{
	/* Replace the old buffer only if I received something in the
	 * last OGM (the OGM could carry no changes)
	 */
	spin_lock_bh(&orig_node->tt_buff_lock);
	if (tt_buff_len > 0) {
		kfree(orig_node->tt_buff);
		orig_node->tt_buff_len = 0;
		orig_node->tt_buff = kmalloc(tt_buff_len, GFP_ATOMIC);
		if (orig_node->tt_buff) {
			memcpy(orig_node->tt_buff, tt_buff, tt_buff_len);
			orig_node->tt_buff_len = tt_buff_len;
		}
	}
	spin_unlock_bh(&orig_node->tt_buff_lock);
}