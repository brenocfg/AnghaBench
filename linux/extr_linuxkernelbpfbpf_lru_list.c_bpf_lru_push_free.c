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
struct bpf_lru_node {int dummy; } ;
struct bpf_lru {scalar_t__ percpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  bpf_common_lru_push_free (struct bpf_lru*,struct bpf_lru_node*) ; 
 int /*<<< orphan*/  bpf_percpu_lru_push_free (struct bpf_lru*,struct bpf_lru_node*) ; 

void bpf_lru_push_free(struct bpf_lru *lru, struct bpf_lru_node *node)
{
	if (lru->percpu)
		bpf_percpu_lru_push_free(lru, node);
	else
		bpf_common_lru_push_free(lru, node);
}