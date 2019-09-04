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
struct wl3501_card {scalar_t__ net_type; } ;

/* Variables and functions */
 scalar_t__ IW_MODE_INFRA ; 
 int WL3501_NET_TYPE_ADHOC ; 
 int WL3501_NET_TYPE_INFRA ; 

__attribute__((used)) static inline int wl3501_fw_bss_type(struct wl3501_card *this)
{
	return this->net_type == IW_MODE_INFRA ? WL3501_NET_TYPE_INFRA :
						 WL3501_NET_TYPE_ADHOC;
}