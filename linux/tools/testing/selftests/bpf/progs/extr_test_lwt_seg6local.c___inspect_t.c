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
typedef  int /*<<< orphan*/  table ;
struct ip6_srh_t {scalar_t__ flags; scalar_t__ tag; int hdrlen; } ;
struct __sk_buff {int dummy; } ;

/* Variables and functions */
 int BPF_DROP ; 
 int BPF_REDIRECT ; 
 int /*<<< orphan*/  SEG6_LOCAL_ACTION_END_T ; 
 scalar_t__ bpf_htons (int) ; 
 int bpf_lwt_seg6_action (struct __sk_buff*,int /*<<< orphan*/ ,void*,int) ; 
 struct ip6_srh_t* get_srh (struct __sk_buff*) ; 

int __inspect_t(struct __sk_buff *skb)
{
	struct ip6_srh_t *srh = get_srh(skb);
	int table = 117;
	int err;

	if (srh == NULL)
		return BPF_DROP;

	if (srh->flags != 0)
		return BPF_DROP;

	if (srh->tag != bpf_htons(2442))
		return BPF_DROP;

	if (srh->hdrlen != 8) // 4 segments
		return BPF_DROP;

	err = bpf_lwt_seg6_action(skb, SEG6_LOCAL_ACTION_END_T,
				  (void *)&table, sizeof(table));

	if (err)
		return BPF_DROP;

	return BPF_REDIRECT;
}