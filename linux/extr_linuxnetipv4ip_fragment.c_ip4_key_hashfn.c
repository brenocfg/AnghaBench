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
struct frag_v4_compare_key {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  jhash2 (void const*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 ip4_key_hashfn(const void *data, u32 len, u32 seed)
{
	return jhash2(data,
		      sizeof(struct frag_v4_compare_key) / sizeof(u32), seed);
}