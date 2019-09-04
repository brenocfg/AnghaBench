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
struct rtllib_device {int softmac_features; scalar_t__ active_scan; } ;

/* Variables and functions */
 int IEEE_SOFTMAC_PROBERQ ; 
 int /*<<< orphan*/  rtllib_send_probe (struct rtllib_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtllib_send_probe_requests(struct rtllib_device *ieee, u8 is_mesh)
{
	if (ieee->active_scan && (ieee->softmac_features &
	    IEEE_SOFTMAC_PROBERQ)) {
		rtllib_send_probe(ieee, 0);
		rtllib_send_probe(ieee, 0);
	}
}