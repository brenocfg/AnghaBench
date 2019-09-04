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
typedef  int /*<<< orphan*/  u16 ;
struct wil_tid_ampdu_rx {int /*<<< orphan*/  head_seq_num; scalar_t__ stored_mpdu_num; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int reorder_index (struct wil_tid_ampdu_rx*,int /*<<< orphan*/ ) ; 
 scalar_t__ seq_less (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wil_release_reorder_frame (struct net_device*,struct wil_tid_ampdu_rx*,int) ; 

__attribute__((used)) static void wil_release_reorder_frames(struct net_device *ndev,
				       struct wil_tid_ampdu_rx *r,
				       u16 hseq)
{
	int index;

	/* note: this function is never called with
	 * hseq preceding r->head_seq_num, i.e it is always true
	 * !seq_less(hseq, r->head_seq_num)
	 * and thus on loop exit it should be
	 * r->head_seq_num == hseq
	 */
	while (seq_less(r->head_seq_num, hseq) && r->stored_mpdu_num) {
		index = reorder_index(r, r->head_seq_num);
		wil_release_reorder_frame(ndev, r, index);
	}
	r->head_seq_num = hseq;
}