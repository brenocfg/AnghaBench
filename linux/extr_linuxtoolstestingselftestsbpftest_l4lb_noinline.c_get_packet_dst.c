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
struct vip_meta {int vip_num; } ;
struct real_definition {int dummy; } ;
struct packet_description {int dummy; } ;
typedef  int __u32 ;

/* Variables and functions */
 int RING_SIZE ; 
 void* bpf_map_lookup_elem (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  ch_rings ; 
 int get_packet_hash (struct packet_description*,int) ; 
 int /*<<< orphan*/  reals ; 

__attribute__((used)) static bool get_packet_dst(struct real_definition **real,
			   struct packet_description *pckt,
			   struct vip_meta *vip_info,
			   bool is_ipv6)
{
	__u32 hash = get_packet_hash(pckt, is_ipv6);
	__u32 key = RING_SIZE * vip_info->vip_num + hash % RING_SIZE;
	__u32 *real_pos;

	if (hash != 0x358459b7 /* jhash of ipv4 packet */  &&
	    hash != 0x2f4bc6bb /* jhash of ipv6 packet */)
		return 0;

	real_pos = bpf_map_lookup_elem(&ch_rings, &key);
	if (!real_pos)
		return false;
	key = *real_pos;
	*real = bpf_map_lookup_elem(&reals, &key);
	if (!(*real))
		return false;
	return true;
}