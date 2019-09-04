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
struct brcms_c_info {int dummy; } ;
struct brcms_ampdu_session {scalar_t__ dma_len; scalar_t__ ampdu_len; scalar_t__ max_ampdu_frames; scalar_t__ max_ampdu_len; int /*<<< orphan*/  skb_list; struct brcms_c_info* wlc; } ;

/* Variables and functions */
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 

void brcms_c_ampdu_reset_session(struct brcms_ampdu_session *session,
				 struct brcms_c_info *wlc)
{
	session->wlc = wlc;
	skb_queue_head_init(&session->skb_list);
	session->max_ampdu_len = 0;    /* determined from first MPDU */
	session->max_ampdu_frames = 0; /* determined from first MPDU */
	session->ampdu_len = 0;
	session->dma_len = 0;
}