#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct btc_coexist {int /*<<< orphan*/  (* btc_write_2byte ) (struct btc_coexist*,int,int) ;} ;
struct TYPE_2__ {int cur_retry_limit_type; int pre_retry_limit_type; int backup_retry_limit; } ;

/* Variables and functions */
 TYPE_1__* coex_dm ; 
 int /*<<< orphan*/  stub1 (struct btc_coexist*,int,int) ; 
 int /*<<< orphan*/  stub2 (struct btc_coexist*,int,int) ; 

__attribute__((used)) static void btc8192e2ant_retry_limit(struct btc_coexist *btcoexist,
				     bool force_exec, u8 type)
{
	coex_dm->cur_retry_limit_type = type;

	if (force_exec || (coex_dm->pre_retry_limit_type !=
			   coex_dm->cur_retry_limit_type)) {
		switch (coex_dm->cur_retry_limit_type) {
		case 0:	/* normal mode */
			btcoexist->btc_write_2byte(btcoexist, 0x42a,
						   coex_dm->backup_retry_limit);
			break;
		case 1:	/* retry limit = 8 */
			btcoexist->btc_write_2byte(btcoexist, 0x42a, 0x0808);
			break;
		default:
			break;
		}
	}

	coex_dm->pre_retry_limit_type = coex_dm->cur_retry_limit_type;
}