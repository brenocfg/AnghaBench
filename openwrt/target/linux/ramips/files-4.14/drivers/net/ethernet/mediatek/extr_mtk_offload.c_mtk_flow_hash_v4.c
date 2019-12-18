#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  s_addr; } ;
struct flow_offload_tuple {TYPE_2__ src_v4; TYPE_1__ dst_v4; int /*<<< orphan*/  dst_port; int /*<<< orphan*/  src_port; } ;

/* Variables and functions */
 int ntohl (int /*<<< orphan*/ ) ; 
 int ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32
mtk_flow_hash_v4(struct flow_offload_tuple *tuple)
{
	u32 ports = ntohs(tuple->src_port)  << 16 | ntohs(tuple->dst_port);
	u32 src = ntohl(tuple->dst_v4.s_addr);
	u32 dst = ntohl(tuple->src_v4.s_addr);
	u32 hash = (ports & src) | ((~ports) & dst);
	u32 hash_23_0 = hash & 0xffffff;
	u32 hash_31_24 = hash & 0xff000000;

	hash = ports ^ src ^ dst ^ ((hash_23_0 << 8) | (hash_31_24 >> 24));
	hash = ((hash & 0xffff0000) >> 16 ) ^ (hash & 0xfffff);
	hash &= 0x7ff;
	hash *= 2;;

	return hash;
}