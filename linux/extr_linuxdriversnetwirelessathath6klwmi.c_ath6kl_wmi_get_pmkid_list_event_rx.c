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
typedef  int u32 ;
struct wmi_pmkid_list_reply {int /*<<< orphan*/  num_pmkid; } ;
struct wmi {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int WMI_PMKID_LEN ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath6kl_wmi_get_pmkid_list_event_rx(struct wmi *wmi, u8 *datap,
					      u32 len)
{
	struct wmi_pmkid_list_reply *reply;
	u32 expected_len;

	if (len < sizeof(struct wmi_pmkid_list_reply))
		return -EINVAL;

	reply = (struct wmi_pmkid_list_reply *)datap;
	expected_len = sizeof(reply->num_pmkid) +
		le32_to_cpu(reply->num_pmkid) * WMI_PMKID_LEN;

	if (len < expected_len)
		return -EINVAL;

	return 0;
}