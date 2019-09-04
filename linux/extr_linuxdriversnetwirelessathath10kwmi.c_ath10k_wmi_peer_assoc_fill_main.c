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
struct wmi_peer_assoc_complete_arg {int dummy; } ;
struct wmi_main_peer_assoc_complete_cmd {int /*<<< orphan*/  peer_ht_info; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath10k_wmi_peer_assoc_fill (struct ath10k*,void*,struct wmi_peer_assoc_complete_arg const*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ath10k_wmi_peer_assoc_fill_main(struct ath10k *ar, void *buf,
				const struct wmi_peer_assoc_complete_arg *arg)
{
	struct wmi_main_peer_assoc_complete_cmd *cmd = buf;

	ath10k_wmi_peer_assoc_fill(ar, buf, arg);
	memset(cmd->peer_ht_info, 0, sizeof(cmd->peer_ht_info));
}