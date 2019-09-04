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
struct wlan_network {int dummy; } ;
typedef  int /*<<< orphan*/  _queue ;

/* Variables and functions */
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int _rtw_enqueue_network (int /*<<< orphan*/ *,struct wlan_network*) ; 

int	rtw_enqueue_network(_queue *queue, struct wlan_network *pnetwork)
{
	int	res;
_func_enter_;		
	res = _rtw_enqueue_network(queue, pnetwork);
_func_exit_;		
	return res;
}