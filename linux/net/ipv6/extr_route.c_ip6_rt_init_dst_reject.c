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
typedef  int u8 ;
struct TYPE_2__ {int /*<<< orphan*/  input; int /*<<< orphan*/  output; int /*<<< orphan*/  error; } ;
struct rt6_info {TYPE_1__ dst; } ;

/* Variables and functions */
#define  RTN_BLACKHOLE 131 
#define  RTN_PROHIBIT 130 
#define  RTN_THROW 129 
#define  RTN_UNREACHABLE 128 
 int /*<<< orphan*/  dst_discard ; 
 int /*<<< orphan*/  dst_discard_out ; 
 int /*<<< orphan*/  ip6_pkt_discard ; 
 int /*<<< orphan*/  ip6_pkt_discard_out ; 
 int /*<<< orphan*/  ip6_pkt_prohibit ; 
 int /*<<< orphan*/  ip6_pkt_prohibit_out ; 
 int /*<<< orphan*/  ip6_rt_type_to_error (int) ; 

__attribute__((used)) static void ip6_rt_init_dst_reject(struct rt6_info *rt, u8 fib6_type)
{
	rt->dst.error = ip6_rt_type_to_error(fib6_type);

	switch (fib6_type) {
	case RTN_BLACKHOLE:
		rt->dst.output = dst_discard_out;
		rt->dst.input = dst_discard;
		break;
	case RTN_PROHIBIT:
		rt->dst.output = ip6_pkt_prohibit_out;
		rt->dst.input = ip6_pkt_prohibit;
		break;
	case RTN_THROW:
	case RTN_UNREACHABLE:
	default:
		rt->dst.output = ip6_pkt_discard_out;
		rt->dst.input = ip6_pkt_discard;
		break;
	}
}