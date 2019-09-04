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
struct brcmf_flowring {int tdls_active; struct brcmf_flowring_tdls_entry* tdls_entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  kfree (struct brcmf_flowring_tdls_entry*) ; 
 struct brcmf_flowring_tdls_entry* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void brcmf_flowring_add_tdls_peer(struct brcmf_flowring *flow, int ifidx,
				  u8 peer[ETH_ALEN])
{
	struct brcmf_flowring_tdls_entry *tdls_entry;
	struct brcmf_flowring_tdls_entry *search;

	tdls_entry = kzalloc(sizeof(*tdls_entry), GFP_ATOMIC);
	if (tdls_entry == NULL)
		return;

	memcpy(tdls_entry->mac, peer, ETH_ALEN);
	tdls_entry->next = NULL;
	if (flow->tdls_entry == NULL) {
		flow->tdls_entry = tdls_entry;
	} else {
		search = flow->tdls_entry;
		if (memcmp(search->mac, peer, ETH_ALEN) == 0)
			goto free_entry;
		while (search->next) {
			search = search->next;
			if (memcmp(search->mac, peer, ETH_ALEN) == 0)
				goto free_entry;
		}
		search->next = tdls_entry;
	}

	flow->tdls_active = true;
	return;

free_entry:
	kfree(tdls_entry);
}