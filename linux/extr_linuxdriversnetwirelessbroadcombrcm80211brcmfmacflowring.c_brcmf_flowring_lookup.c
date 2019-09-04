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
typedef  size_t u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct brcmf_flowring_hash {size_t fifo; size_t ifidx; int flowid; int /*<<< orphan*/  mac; } ;
struct brcmf_flowring {scalar_t__* addr_mode; struct brcmf_flowring_hash* hash; scalar_t__ tdls_active; } ;

/* Variables and functions */
 scalar_t__ ADDR_INDIRECT ; 
 scalar_t__ ALLFFMAC ; 
 int BRCMF_FLOWRING_HASHSIZE ; 
 int BRCMF_FLOWRING_HASH_AP (size_t*,size_t,size_t) ; 
 int BRCMF_FLOWRING_HASH_STA (size_t,size_t) ; 
 int BRCMF_FLOWRING_INVALID_ID ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 scalar_t__ brcmf_flowring_is_tdls_mac (struct brcmf_flowring*,size_t*) ; 
 size_t* brcmf_flowring_prio2fifo ; 
 scalar_t__ is_multicast_ether_addr (size_t*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,size_t*,int /*<<< orphan*/ ) ; 

u32 brcmf_flowring_lookup(struct brcmf_flowring *flow, u8 da[ETH_ALEN],
			  u8 prio, u8 ifidx)
{
	struct brcmf_flowring_hash *hash;
	u16 hash_idx;
	u32 i;
	bool found;
	bool sta;
	u8 fifo;
	u8 *mac;

	fifo = brcmf_flowring_prio2fifo[prio];
	sta = (flow->addr_mode[ifidx] == ADDR_INDIRECT);
	mac = da;
	if ((!sta) && (is_multicast_ether_addr(da))) {
		mac = (u8 *)ALLFFMAC;
		fifo = 0;
	}
	if ((sta) && (flow->tdls_active) &&
	    (brcmf_flowring_is_tdls_mac(flow, da))) {
		sta = false;
	}
	hash_idx =  sta ? BRCMF_FLOWRING_HASH_STA(fifo, ifidx) :
			  BRCMF_FLOWRING_HASH_AP(mac, fifo, ifidx);
	hash_idx &= (BRCMF_FLOWRING_HASHSIZE - 1);
	found = false;
	hash = flow->hash;
	for (i = 0; i < BRCMF_FLOWRING_HASHSIZE; i++) {
		if ((sta || (memcmp(hash[hash_idx].mac, mac, ETH_ALEN) == 0)) &&
		    (hash[hash_idx].fifo == fifo) &&
		    (hash[hash_idx].ifidx == ifidx)) {
			found = true;
			break;
		}
		hash_idx++;
		hash_idx &= (BRCMF_FLOWRING_HASHSIZE - 1);
	}
	if (found)
		return hash[hash_idx].flowid;

	return BRCMF_FLOWRING_INVALID_ID;
}