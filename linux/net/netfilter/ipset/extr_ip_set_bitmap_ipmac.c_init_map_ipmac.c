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
typedef  void* u32 ;
struct ip_set {int /*<<< orphan*/  family; struct bitmap_ipmac* data; int /*<<< orphan*/  timeout; } ;
struct bitmap_ipmac {struct ip_set* set; void* elements; void* last_ip; void* first_ip; int /*<<< orphan*/  members; int /*<<< orphan*/  memsize; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPSET_NO_TIMEOUT ; 
 int /*<<< orphan*/  NFPROTO_IPV4 ; 
 int /*<<< orphan*/  ip_set_alloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
init_map_ipmac(struct ip_set *set, struct bitmap_ipmac *map,
	       u32 first_ip, u32 last_ip, u32 elements)
{
	map->members = ip_set_alloc(map->memsize);
	if (!map->members)
		return false;
	map->first_ip = first_ip;
	map->last_ip = last_ip;
	map->elements = elements;
	set->timeout = IPSET_NO_TIMEOUT;

	map->set = set;
	set->data = map;
	set->family = NFPROTO_IPV4;

	return true;
}