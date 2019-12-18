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
struct ECPGtype_information_cache {int oid; int isarray; struct ECPGtype_information_cache* next; } ;
typedef  enum ARRAY_TYPE { ____Placeholder_ARRAY_TYPE } ARRAY_TYPE ;

/* Variables and functions */
 scalar_t__ ecpg_alloc (int,int) ; 

__attribute__((used)) static bool
ecpg_type_infocache_push(struct ECPGtype_information_cache **cache, int oid, enum ARRAY_TYPE isarray, int lineno)
{
	struct ECPGtype_information_cache *new_entry
	= (struct ECPGtype_information_cache *) ecpg_alloc(sizeof(struct ECPGtype_information_cache), lineno);

	if (new_entry == NULL)
		return false;

	new_entry->oid = oid;
	new_entry->isarray = isarray;
	new_entry->next = *cache;
	*cache = new_entry;
	return true;
}