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
struct extent_buffer {int dummy; } ;

/* Variables and functions */
 int btrfs_header_flags (struct extent_buffer const*) ; 

__attribute__((used)) static inline int btrfs_header_flag(const struct extent_buffer *eb, u64 flag)
{
	return (btrfs_header_flags(eb) & flag) == flag;
}