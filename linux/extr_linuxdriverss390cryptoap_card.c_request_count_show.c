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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct ap_card {int /*<<< orphan*/  total_request_count; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  ap_list_lock ; 
 unsigned int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 struct ap_card* to_ap_card (struct device*) ; 

__attribute__((used)) static ssize_t request_count_show(struct device *dev,
				  struct device_attribute *attr,
				  char *buf)
{
	struct ap_card *ac = to_ap_card(dev);
	unsigned int req_cnt;

	req_cnt = 0;
	spin_lock_bh(&ap_list_lock);
	req_cnt = atomic_read(&ac->total_request_count);
	spin_unlock_bh(&ap_list_lock);
	return snprintf(buf, PAGE_SIZE, "%d\n", req_cnt);
}