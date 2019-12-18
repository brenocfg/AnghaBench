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

/* Variables and functions */
 int BPF_F_RDONLY ; 
 int BPF_F_WRONLY ; 

__attribute__((used)) static u32 bpf_map_flags_retain_permanent(u32 flags)
{
	/* Some map creation flags are not tied to the map object but
	 * rather to the map fd instead, so they have no meaning upon
	 * map object inspection since multiple file descriptors with
	 * different (access) properties can exist here. Thus, given
	 * this has zero meaning for the map itself, lets clear these
	 * from here.
	 */
	return flags & ~(BPF_F_RDONLY | BPF_F_WRONLY);
}