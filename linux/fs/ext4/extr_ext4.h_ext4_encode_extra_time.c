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
struct timespec64 {int tv_sec; int tv_nsec; } ;
typedef  int s32 ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int EXT4_EPOCH_BITS ; 
 int EXT4_EPOCH_MASK ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 

__attribute__((used)) static inline __le32 ext4_encode_extra_time(struct timespec64 *time)
{
	u32 extra =((time->tv_sec - (s32)time->tv_sec) >> 32) & EXT4_EPOCH_MASK;
	return cpu_to_le32(extra | (time->tv_nsec << EXT4_EPOCH_BITS));
}