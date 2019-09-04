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
struct wlan_network {int dummy; } ;
struct __queue {int dummy; } ;

/* Variables and functions */
 struct wlan_network* _rtw_find_network (struct __queue*,int /*<<< orphan*/ *) ; 

struct	wlan_network *rtw_find_network(struct __queue *scanned_queue, u8 *addr)
{
	struct	wlan_network *pnetwork = _rtw_find_network(scanned_queue, addr);

	return pnetwork;
}