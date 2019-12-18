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
 int /*<<< orphan*/  free (struct hashmap*) ; 
 int /*<<< orphan*/  hashmap__clear (struct hashmap*) ; 

void hashmap__free(struct hashmap *map)
{
	if (!map)
		return;

	hashmap__clear(map);
	free(map);
}