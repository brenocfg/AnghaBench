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
struct sk_buff {int dummy; } ;
struct brcms_ampdu_session {int dummy; } ;
struct dma_info {struct brcms_ampdu_session ampdu_session; } ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  ampdu_finalize (struct dma_info*) ; 
 int brcms_c_ampdu_add_frame (struct brcms_ampdu_session*,struct sk_buff*) ; 

__attribute__((used)) static void prep_ampdu_frame(struct dma_info *di, struct sk_buff *p)
{
	struct brcms_ampdu_session *session = &di->ampdu_session;
	int ret;

	ret = brcms_c_ampdu_add_frame(session, p);
	if (ret == -ENOSPC) {
		/*
		 * AMPDU cannot accomodate this frame. Close out the in-
		 * progress AMPDU session and start a new one.
		 */
		ampdu_finalize(di);
		ret = brcms_c_ampdu_add_frame(session, p);
	}

	WARN_ON(ret);
}