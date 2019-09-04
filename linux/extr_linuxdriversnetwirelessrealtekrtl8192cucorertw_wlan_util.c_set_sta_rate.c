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
struct sta_info {int /*<<< orphan*/  mac_id; } ;
typedef  int /*<<< orphan*/  _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  enable_rate_adaptive (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void set_sta_rate(_adapter *padapter, struct sta_info *psta)
{
	//rate adaptive	
	enable_rate_adaptive(padapter, psta->mac_id);
}