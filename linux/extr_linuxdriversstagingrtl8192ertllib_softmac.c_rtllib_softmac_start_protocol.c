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
struct rtllib_device {int /*<<< orphan*/  wx_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtllib_start_protocol (struct rtllib_device*) ; 

void rtllib_softmac_start_protocol(struct rtllib_device *ieee, u8 mesh_flag)
{
	mutex_lock(&ieee->wx_mutex);
	rtllib_start_protocol(ieee);
	mutex_unlock(&ieee->wx_mutex);
}