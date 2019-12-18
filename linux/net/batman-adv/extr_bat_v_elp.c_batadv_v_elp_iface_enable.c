#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  elp_wq; int /*<<< orphan*/  flags; int /*<<< orphan*/  elp_seqno; int /*<<< orphan*/  elp_skb; } ;
struct batadv_hard_iface {TYPE_1__ bat_v; } ;
struct batadv_elp_packet {int /*<<< orphan*/  version; int /*<<< orphan*/  packet_type; } ;
typedef  int /*<<< orphan*/  random_seqno ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  BATADV_COMPAT_VERSION ; 
 int /*<<< orphan*/  BATADV_ELP ; 
 size_t const BATADV_ELP_HLEN ; 
 int /*<<< orphan*/  BATADV_FULL_DUPLEX ; 
 int /*<<< orphan*/  BATADV_WARNING_DEFAULT ; 
 int ENOMEM ; 
 size_t const ETH_HLEN ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t const NET_IP_ALIGN ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ batadv_is_wifi_hardif (struct batadv_hard_iface*) ; 
 int /*<<< orphan*/  batadv_v_elp_periodic_work ; 
 int /*<<< orphan*/  batadv_v_elp_start_timer (struct batadv_hard_iface*) ; 
 int /*<<< orphan*/  dev_alloc_skb (size_t) ; 
 int /*<<< orphan*/  get_random_bytes (int /*<<< orphan*/ *,int) ; 
 unsigned char* skb_put_zero (int /*<<< orphan*/ ,size_t const) ; 
 int /*<<< orphan*/  skb_reserve (int /*<<< orphan*/ ,size_t const) ; 

int batadv_v_elp_iface_enable(struct batadv_hard_iface *hard_iface)
{
	static const size_t tvlv_padding = sizeof(__be32);
	struct batadv_elp_packet *elp_packet;
	unsigned char *elp_buff;
	u32 random_seqno;
	size_t size;
	int res = -ENOMEM;

	size = ETH_HLEN + NET_IP_ALIGN + BATADV_ELP_HLEN + tvlv_padding;
	hard_iface->bat_v.elp_skb = dev_alloc_skb(size);
	if (!hard_iface->bat_v.elp_skb)
		goto out;

	skb_reserve(hard_iface->bat_v.elp_skb, ETH_HLEN + NET_IP_ALIGN);
	elp_buff = skb_put_zero(hard_iface->bat_v.elp_skb,
				BATADV_ELP_HLEN + tvlv_padding);
	elp_packet = (struct batadv_elp_packet *)elp_buff;

	elp_packet->packet_type = BATADV_ELP;
	elp_packet->version = BATADV_COMPAT_VERSION;

	/* randomize initial seqno to avoid collision */
	get_random_bytes(&random_seqno, sizeof(random_seqno));
	atomic_set(&hard_iface->bat_v.elp_seqno, random_seqno);

	/* assume full-duplex by default */
	hard_iface->bat_v.flags |= BATADV_FULL_DUPLEX;

	/* warn the user (again) if there is no throughput data is available */
	hard_iface->bat_v.flags &= ~BATADV_WARNING_DEFAULT;

	if (batadv_is_wifi_hardif(hard_iface))
		hard_iface->bat_v.flags &= ~BATADV_FULL_DUPLEX;

	INIT_DELAYED_WORK(&hard_iface->bat_v.elp_wq,
			  batadv_v_elp_periodic_work);
	batadv_v_elp_start_timer(hard_iface);
	res = 0;

out:
	return res;
}