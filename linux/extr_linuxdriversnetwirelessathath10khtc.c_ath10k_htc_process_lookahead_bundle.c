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
typedef  int /*<<< orphan*/  u8 ;
struct ath10k_htc_lookahead_bundle {int /*<<< orphan*/  lookahead; } ;
struct ath10k_htc {struct ath10k* ar; } ;
struct ath10k {int dummy; } ;
typedef  enum ath10k_htc_ep_id { ____Placeholder_ath10k_htc_ep_id } ath10k_htc_ep_id ;

/* Variables and functions */
 int EINVAL ; 
 int HTC_HOST_MAX_MSG_PER_RX_BUNDLE ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ath10k_htc_process_lookahead_bundle(struct ath10k_htc *htc,
				    const struct ath10k_htc_lookahead_bundle *report,
				    int len,
				    enum ath10k_htc_ep_id eid,
				    void *next_lookaheads,
				    int *next_lookaheads_len)
{
	struct ath10k *ar = htc->ar;
	int bundle_cnt = len / sizeof(*report);

	if (!bundle_cnt || (bundle_cnt > HTC_HOST_MAX_MSG_PER_RX_BUNDLE)) {
		ath10k_warn(ar, "Invalid lookahead bundle count: %d\n",
			    bundle_cnt);
		return -EINVAL;
	}

	if (next_lookaheads && next_lookaheads_len) {
		int i;

		for (i = 0; i < bundle_cnt; i++) {
			memcpy(((u8 *)next_lookaheads) + 4 * i,
			       report->lookahead, 4);
			report++;
		}

		*next_lookaheads_len = bundle_cnt;
	}

	return 0;
}