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
struct hashmap {int dummy; } ;
typedef  int /*<<< orphan*/  hashmap_hash_fn ;
typedef  int /*<<< orphan*/  hashmap_equal_fn ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct hashmap* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hashmap__init (struct hashmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 struct hashmap* malloc (int) ; 

struct hashmap *hashmap__new(hashmap_hash_fn hash_fn,
			     hashmap_equal_fn equal_fn,
			     void *ctx)
{
	struct hashmap *map = malloc(sizeof(struct hashmap));

	if (!map)
		return ERR_PTR(-ENOMEM);
	hashmap__init(map, hash_fn, equal_fn, ctx);
	return map;
}