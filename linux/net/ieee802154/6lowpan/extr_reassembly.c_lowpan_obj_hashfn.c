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
struct inet_frag_queue {int /*<<< orphan*/  key; } ;
struct frag_lowpan_compare_key {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  jhash2 (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 lowpan_obj_hashfn(const void *data, u32 len, u32 seed)
{
	const struct inet_frag_queue *fq = data;

	return jhash2((const u32 *)&fq->key,
		      sizeof(struct frag_lowpan_compare_key) / sizeof(u32), seed);
}