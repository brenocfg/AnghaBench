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
typedef  int u8 ;
struct btc_coexist {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  btc8821a1ant_ampdu_max_time (struct btc_coexist*,int,int) ; 
 int /*<<< orphan*/  btc8821a1ant_auto_rate_fb_retry (struct btc_coexist*,int,int) ; 
 int /*<<< orphan*/  btc8821a1ant_retry_limit (struct btc_coexist*,int,int) ; 
 int /*<<< orphan*/  btc8821a1ant_update_ra_mask (struct btc_coexist*,int,int) ; 

__attribute__((used)) static void btc8821a1ant_limited_tx(struct btc_coexist *btcoexist,
				    bool force_exec, u8 ra_mask_type,
				    u8 arfr_type, u8 retry_limit_type,
				    u8 ampdu_time_type)
{
	switch (ra_mask_type) {
	case 0:	/* normal mode */
		btc8821a1ant_update_ra_mask(btcoexist, force_exec, 0x0);
		break;
	case 1:	/* disable cck 1/2 */
		btc8821a1ant_update_ra_mask(btcoexist, force_exec,
					    0x00000003);
		break;
	case 2:	/* disable cck 1/2/5.5, ofdm 6/9/12/18/24, mcs 0/1/2/3/4 */
		btc8821a1ant_update_ra_mask(btcoexist, force_exec,
					    0x0001f1f7);
		break;
	default:
		break;
	}

	btc8821a1ant_auto_rate_fb_retry(btcoexist, force_exec, arfr_type);
	btc8821a1ant_retry_limit(btcoexist, force_exec, retry_limit_type);
	btc8821a1ant_ampdu_max_time(btcoexist, force_exec, ampdu_time_type);
}