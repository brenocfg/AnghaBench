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
typedef  int /*<<< orphan*/  u32 ;
struct fd {int dummy; } ;
struct bpf_map {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct bpf_map*) ; 
 struct bpf_map* __bpf_map_get (struct fd) ; 
 struct bpf_map* bpf_map_inc (struct bpf_map*,int) ; 
 struct fd fdget (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdput (struct fd) ; 

struct bpf_map *bpf_map_get_with_uref(u32 ufd)
{
	struct fd f = fdget(ufd);
	struct bpf_map *map;

	map = __bpf_map_get(f);
	if (IS_ERR(map))
		return map;

	map = bpf_map_inc(map, true);
	fdput(f);

	return map;
}