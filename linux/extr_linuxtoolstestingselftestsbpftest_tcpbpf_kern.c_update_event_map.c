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
struct tcpbpf_globals {int event_map; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_ANY ; 
 struct tcpbpf_globals* bpf_map_lookup_elem (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bpf_map_update_elem (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct tcpbpf_globals*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  global_map ; 

__attribute__((used)) static inline void update_event_map(int event)
{
	__u32 key = 0;
	struct tcpbpf_globals g, *gp;

	gp = bpf_map_lookup_elem(&global_map, &key);
	if (gp == NULL) {
		struct tcpbpf_globals g = {0};

		g.event_map |= (1 << event);
		bpf_map_update_elem(&global_map, &key, &g,
			    BPF_ANY);
	} else {
		g = *gp;
		g.event_map |= (1 << event);
		bpf_map_update_elem(&global_map, &key, &g,
			    BPF_ANY);
	}
}