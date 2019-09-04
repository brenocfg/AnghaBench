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
typedef  int /*<<< orphan*/  uint32_t ;
struct stats {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_MAP_TYPE_HASH ; 
 scalar_t__ bpf_create_map (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ map_fd ; 

__attribute__((used)) static void maps_create(void)
{
	map_fd = bpf_create_map(BPF_MAP_TYPE_HASH, sizeof(uint32_t),
				sizeof(struct stats), 100, 0);
	if (map_fd < 0)
		error(1, errno, "map create failed!\n");
}