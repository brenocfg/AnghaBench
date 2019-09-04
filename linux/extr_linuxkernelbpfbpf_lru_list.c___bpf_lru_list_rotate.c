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
struct bpf_lru_list {int dummy; } ;
struct bpf_lru {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __bpf_lru_list_rotate_active (struct bpf_lru*,struct bpf_lru_list*) ; 
 int /*<<< orphan*/  __bpf_lru_list_rotate_inactive (struct bpf_lru*,struct bpf_lru_list*) ; 
 scalar_t__ bpf_lru_list_inactive_low (struct bpf_lru_list*) ; 

__attribute__((used)) static void __bpf_lru_list_rotate(struct bpf_lru *lru, struct bpf_lru_list *l)
{
	if (bpf_lru_list_inactive_low(l))
		__bpf_lru_list_rotate_active(lru, l);

	__bpf_lru_list_rotate_inactive(lru, l);
}