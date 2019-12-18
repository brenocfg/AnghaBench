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
typedef  int u32 ;
struct sk_psock_progs {int /*<<< orphan*/  skb_verdict; int /*<<< orphan*/  skb_parser; int /*<<< orphan*/  msg_parser; } ;
struct bpf_prog {int dummy; } ;
struct bpf_map {int dummy; } ;

/* Variables and functions */
#define  BPF_SK_MSG_VERDICT 130 
#define  BPF_SK_SKB_STREAM_PARSER 129 
#define  BPF_SK_SKB_STREAM_VERDICT 128 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  psock_set_prog (int /*<<< orphan*/ *,struct bpf_prog*) ; 
 struct sk_psock_progs* sock_map_progs (struct bpf_map*) ; 

int sock_map_prog_update(struct bpf_map *map, struct bpf_prog *prog,
			 u32 which)
{
	struct sk_psock_progs *progs = sock_map_progs(map);

	if (!progs)
		return -EOPNOTSUPP;

	switch (which) {
	case BPF_SK_MSG_VERDICT:
		psock_set_prog(&progs->msg_parser, prog);
		break;
	case BPF_SK_SKB_STREAM_PARSER:
		psock_set_prog(&progs->skb_parser, prog);
		break;
	case BPF_SK_SKB_STREAM_VERDICT:
		psock_set_prog(&progs->skb_verdict, prog);
		break;
	default:
		return -EOPNOTSUPP;
	}

	return 0;
}