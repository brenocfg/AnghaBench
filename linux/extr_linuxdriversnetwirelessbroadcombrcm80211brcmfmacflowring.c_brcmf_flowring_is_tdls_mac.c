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
struct brcmf_flowring_tdls_entry {struct brcmf_flowring_tdls_entry* next; int /*<<< orphan*/  mac; } ;
struct brcmf_flowring {struct brcmf_flowring_tdls_entry* tdls_entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
brcmf_flowring_is_tdls_mac(struct brcmf_flowring *flow, u8 mac[ETH_ALEN])
{
	struct brcmf_flowring_tdls_entry *search;

	search = flow->tdls_entry;

	while (search) {
		if (memcmp(search->mac, mac, ETH_ALEN) == 0)
			return true;
		search = search->next;
	}

	return false;
}