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
typedef  scalar_t__ u64 ;
typedef  size_t u32 ;
struct log_entry {int dummy; } ;
struct arena_info {size_t* log_index; scalar_t__ logoff; } ;

/* Variables and functions */
 int LOG_ENT_SIZE ; 
 size_t LOG_GRP_SIZE ; 
 int arena_write_bytes (struct arena_info*,scalar_t__,void*,unsigned int,unsigned long) ; 

__attribute__((used)) static int __btt_log_write(struct arena_info *arena, u32 lane,
			u32 sub, struct log_entry *ent, unsigned long flags)
{
	int ret;
	u32 group_slot = arena->log_index[sub];
	unsigned int log_half = LOG_ENT_SIZE / 2;
	void *src = ent;
	u64 ns_off;

	ns_off = arena->logoff + (lane * LOG_GRP_SIZE) +
		(group_slot * LOG_ENT_SIZE);
	/* split the 16B write into atomic, durable halves */
	ret = arena_write_bytes(arena, ns_off, src, log_half, flags);
	if (ret)
		return ret;

	ns_off += log_half;
	src += log_half;
	return arena_write_bytes(arena, ns_off, src, log_half, flags);
}