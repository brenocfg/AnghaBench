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
struct wl3501_card {int /*<<< orphan*/  bssid; int /*<<< orphan*/  cap_info; } ;
struct wl3501_assoc_req {int timeout; int listen_interval; int /*<<< orphan*/  mac_addr; int /*<<< orphan*/  cap_info; int /*<<< orphan*/  sig_id; } ;
typedef  int /*<<< orphan*/  sig ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  WL3501_SIG_ASSOC_REQ ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int wl3501_esbq_exec (struct wl3501_card*,struct wl3501_assoc_req*,int) ; 

__attribute__((used)) static int wl3501_mgmt_association(struct wl3501_card *this)
{
	struct wl3501_assoc_req sig = {
		.sig_id		 = WL3501_SIG_ASSOC_REQ,
		.timeout	 = 1000,
		.listen_interval = 5,
		.cap_info	 = this->cap_info,
	};

	pr_debug("entry");
	memcpy(sig.mac_addr, this->bssid, ETH_ALEN);
	return wl3501_esbq_exec(this, &sig, sizeof(sig));
}