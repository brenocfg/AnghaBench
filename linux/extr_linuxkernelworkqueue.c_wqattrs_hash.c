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
struct workqueue_attrs {int /*<<< orphan*/  cpumask; int /*<<< orphan*/  nice; } ;

/* Variables and functions */
 int BITS_TO_LONGS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jhash (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jhash_1word (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nr_cpumask_bits ; 

__attribute__((used)) static u32 wqattrs_hash(const struct workqueue_attrs *attrs)
{
	u32 hash = 0;

	hash = jhash_1word(attrs->nice, hash);
	hash = jhash(cpumask_bits(attrs->cpumask),
		     BITS_TO_LONGS(nr_cpumask_bits) * sizeof(long), hash);
	return hash;
}