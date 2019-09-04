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
struct vip_meta {int flags; int vip_num; } ;
struct real_pos_lru {int atime; int pos; } ;
struct real_definition {int dummy; } ;
struct TYPE_2__ {scalar_t__ proto; int /*<<< orphan*/  srcv6; int /*<<< orphan*/ * port16; } ;
struct packet_description {TYPE_1__ flow; } ;
struct lb_stats {int v2; int v1; } ;
typedef  int __u64 ;
typedef  int __u32 ;

/* Variables and functions */
 scalar_t__ IPPROTO_UDP ; 
 int bpf_ktime_get_ns () ; 
 void* bpf_map_lookup_elem (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  bpf_map_update_elem (void*,TYPE_1__*,struct real_pos_lru*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ch_rings ; 
 int get_packet_hash (struct packet_description*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reals ; 
 int /*<<< orphan*/  stats ; 

__attribute__((used)) __attribute__ ((noinline))
static bool get_packet_dst(struct real_definition **real,
			   struct packet_description *pckt,
			   struct vip_meta *vip_info,
			   bool is_ipv6, void *lru_map)
{
	struct real_pos_lru new_dst_lru = { };
	bool hash_16bytes = is_ipv6;
	__u32 *real_pos, hash, key;
	__u64 cur_time;

	if (vip_info->flags & (1 << 2))
		hash_16bytes = 1;
	if (vip_info->flags & (1 << 3)) {
		pckt->flow.port16[0] = pckt->flow.port16[1];
		memset(pckt->flow.srcv6, 0, 16);
	}
	hash = get_packet_hash(pckt, hash_16bytes);
	if (hash != 0x358459b7 /* jhash of ipv4 packet */  &&
	    hash != 0x2f4bc6bb /* jhash of ipv6 packet */)
		return 0;
	key = 2 * vip_info->vip_num + hash % 2;
	real_pos = bpf_map_lookup_elem(&ch_rings, &key);
	if (!real_pos)
		return 0;
	key = *real_pos;
	*real = bpf_map_lookup_elem(&reals, &key);
	if (!(*real))
		return 0;
	if (!(vip_info->flags & (1 << 1))) {
		__u32 conn_rate_key = 512 + 2;
		struct lb_stats *conn_rate_stats =
		    bpf_map_lookup_elem(&stats, &conn_rate_key);

		if (!conn_rate_stats)
			return 1;
		cur_time = bpf_ktime_get_ns();
		if ((cur_time - conn_rate_stats->v2) >> 32 > 0xffFFFF) {
			conn_rate_stats->v1 = 1;
			conn_rate_stats->v2 = cur_time;
		} else {
			conn_rate_stats->v1 += 1;
			if (conn_rate_stats->v1 >= 1)
				return 1;
		}
		if (pckt->flow.proto == IPPROTO_UDP)
			new_dst_lru.atime = cur_time;
		new_dst_lru.pos = key;
		bpf_map_update_elem(lru_map, &pckt->flow, &new_dst_lru, 0);
	}
	return 1;
}