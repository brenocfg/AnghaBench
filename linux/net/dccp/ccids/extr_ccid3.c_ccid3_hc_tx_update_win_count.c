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
typedef  int u32 ;
struct ccid3_hc_tx_sock {int tx_rtt; int tx_last_win_count; int /*<<< orphan*/  tx_t_last_win_count; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int ktime_us_delta (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ min (int,unsigned int) ; 

__attribute__((used)) static inline void ccid3_hc_tx_update_win_count(struct ccid3_hc_tx_sock *hc,
						ktime_t now)
{
	u32 delta = ktime_us_delta(now, hc->tx_t_last_win_count),
	    quarter_rtts = (4 * delta) / hc->tx_rtt;

	if (quarter_rtts > 0) {
		hc->tx_t_last_win_count = now;
		hc->tx_last_win_count  += min(quarter_rtts, 5U);
		hc->tx_last_win_count  &= 0xF;		/* mod 16 */
	}
}