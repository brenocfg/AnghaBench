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
struct hlist_head {int dummy; } ;
struct bpf_dtab {int n_buckets; struct hlist_head* dev_index_head; } ;

/* Variables and functions */

__attribute__((used)) static inline struct hlist_head *dev_map_index_hash(struct bpf_dtab *dtab,
						    int idx)
{
	return &dtab->dev_index_head[idx & (dtab->n_buckets - 1)];
}