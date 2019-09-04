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
struct wmi_cmd_hdr {int /*<<< orphan*/  cmd_id; } ;

/* Variables and functions */
 unsigned int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline unsigned int ath6kl_get_wmi_id(void *buf, size_t buf_len)
{
	struct wmi_cmd_hdr *hdr = buf;

	if (buf_len < sizeof(*hdr))
		return 0;

	return le16_to_cpu(hdr->cmd_id);
}