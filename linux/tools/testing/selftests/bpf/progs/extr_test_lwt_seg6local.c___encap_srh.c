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
struct ip6_srh_t {int hdrlen; int type; int segments_left; int first_segment; scalar_t__ tag; scalar_t__ flags; scalar_t__ nexthdr; } ;
struct ip6_addr_t {void* hi; void* lo; } ;
struct __sk_buff {int dummy; } ;
typedef  int /*<<< orphan*/  srh_buf ;

/* Variables and functions */
 int BPF_DROP ; 
 int BPF_REDIRECT ; 
 void* bpf_cpu_to_be64 (unsigned long long) ; 
 int bpf_lwt_push_encap (struct __sk_buff*,int /*<<< orphan*/ ,void*,int) ; 

int __encap_srh(struct __sk_buff *skb)
{
	unsigned long long hi = 0xfd00000000000000;
	struct ip6_addr_t *seg;
	struct ip6_srh_t *srh;
	char srh_buf[72]; // room for 4 segments
	int err;

	srh = (struct ip6_srh_t *)srh_buf;
	srh->nexthdr = 0;
	srh->hdrlen = 8;
	srh->type = 4;
	srh->segments_left = 3;
	srh->first_segment = 3;
	srh->flags = 0;
	srh->tag = 0;

	seg = (struct ip6_addr_t *)((char *)srh + sizeof(*srh));

	#pragma clang loop unroll(full)
	for (unsigned long long lo = 0; lo < 4; lo++) {
		seg->lo = bpf_cpu_to_be64(4 - lo);
		seg->hi = bpf_cpu_to_be64(hi);
		seg = (struct ip6_addr_t *)((char *)seg + sizeof(*seg));
	}

	err = bpf_lwt_push_encap(skb, 0, (void *)srh, sizeof(srh_buf));
	if (err)
		return BPF_DROP;

	return BPF_REDIRECT;
}