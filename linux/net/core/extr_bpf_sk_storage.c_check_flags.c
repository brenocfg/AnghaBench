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
typedef  int u64 ;
struct bpf_sk_storage_data {int dummy; } ;

/* Variables and functions */
 int BPF_EXIST ; 
 int BPF_F_LOCK ; 
 int BPF_NOEXIST ; 
 int EEXIST ; 
 int ENOENT ; 

__attribute__((used)) static int check_flags(const struct bpf_sk_storage_data *old_sdata,
		       u64 map_flags)
{
	if (old_sdata && (map_flags & ~BPF_F_LOCK) == BPF_NOEXIST)
		/* elem already exists */
		return -EEXIST;

	if (!old_sdata && (map_flags & ~BPF_F_LOCK) == BPF_EXIST)
		/* elem doesn't exist, cannot update it */
		return -ENOENT;

	return 0;
}