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
struct avtab_key {int /*<<< orphan*/  source_type; int /*<<< orphan*/  target_type; int /*<<< orphan*/  target_class; } ;

/* Variables and functions */
 int /*<<< orphan*/  mix (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int avtab_hash(struct avtab_key *keyp, u32 mask)
{
	static const u32 c1 = 0xcc9e2d51;
	static const u32 c2 = 0x1b873593;
	static const u32 r1 = 15;
	static const u32 r2 = 13;
	static const u32 m  = 5;
	static const u32 n  = 0xe6546b64;

	u32 hash = 0;

#define mix(input) { \
	u32 v = input; \
	v *= c1; \
	v = (v << r1) | (v >> (32 - r1)); \
	v *= c2; \
	hash ^= v; \
	hash = (hash << r2) | (hash >> (32 - r2)); \
	hash = hash * m + n; \
}

	mix(keyp->target_class);
	mix(keyp->target_type);
	mix(keyp->source_type);

#undef mix

	hash ^= hash >> 16;
	hash *= 0x85ebca6b;
	hash ^= hash >> 13;
	hash *= 0xc2b2ae35;
	hash ^= hash >> 16;

	return hash & mask;
}