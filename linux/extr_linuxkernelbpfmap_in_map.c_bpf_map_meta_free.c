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
struct bpf_map {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct bpf_map*) ; 

void bpf_map_meta_free(struct bpf_map *map_meta)
{
	kfree(map_meta);
}