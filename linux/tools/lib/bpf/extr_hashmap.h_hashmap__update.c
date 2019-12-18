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

/* Variables and functions */
 int /*<<< orphan*/  HASHMAP_UPDATE ; 
 int hashmap__insert (struct hashmap*,void const*,void*,int /*<<< orphan*/ ,void const**,void**) ; 

__attribute__((used)) static inline int hashmap__update(struct hashmap *map,
				  const void *key, void *value,
				  const void **old_key, void **old_value)
{
	return hashmap__insert(map, key, value, HASHMAP_UPDATE,
			       old_key, old_value);
}