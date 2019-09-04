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
 struct wlan_network* _rtw_dequeue_network (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct	wlan_network *rtw_dequeue_network(_queue *queue)
{
	struct wlan_network *pnetwork;
_func_enter_;		
	pnetwork = _rtw_dequeue_network(queue);
_func_exit_;		
	return pnetwork;
}