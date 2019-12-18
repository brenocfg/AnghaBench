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
struct bpf_map_memory {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct bpf_map_memory*,int /*<<< orphan*/ ,int) ; 

void bpf_map_charge_move(struct bpf_map_memory *dst,
			 struct bpf_map_memory *src)
{
	*dst = *src;

	/* Make sure src will not be used for the redundant uncharging. */
	memset(src, 0, sizeof(struct bpf_map_memory));
}