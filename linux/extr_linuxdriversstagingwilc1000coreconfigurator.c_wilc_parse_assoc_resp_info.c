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
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct connect_info {scalar_t__ status; scalar_t__ resp_ies_len; int /*<<< orphan*/  resp_ies; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 size_t AID_LEN ; 
 size_t CAP_INFO_LEN ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t STATUS_CODE_LEN ; 
 scalar_t__ WLAN_STATUS_SUCCESS ; 
 scalar_t__ get_asoc_status (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmemdup (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 

s32 wilc_parse_assoc_resp_info(u8 *buffer, u32 buffer_len,
			       struct connect_info *ret_conn_info)
{
	u8 *ies;
	u16 ies_len;

	ret_conn_info->status = get_asoc_status(buffer);
	if (ret_conn_info->status == WLAN_STATUS_SUCCESS) {
		ies = &buffer[CAP_INFO_LEN + STATUS_CODE_LEN + AID_LEN];
		ies_len = buffer_len - (CAP_INFO_LEN + STATUS_CODE_LEN +
					AID_LEN);

		ret_conn_info->resp_ies = kmemdup(ies, ies_len, GFP_KERNEL);
		if (!ret_conn_info->resp_ies)
			return -ENOMEM;

		ret_conn_info->resp_ies_len = ies_len;
	}

	return 0;
}