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
struct auxtrace_cache_entry {int /*<<< orphan*/  hash; int /*<<< orphan*/  key; } ;
struct auxtrace_cache {scalar_t__ limit; scalar_t__ cnt; int /*<<< orphan*/  bits; int /*<<< orphan*/ * hashtable; } ;

/* Variables and functions */
 int /*<<< orphan*/  auxtrace_cache__drop (struct auxtrace_cache*) ; 
 size_t hash_32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int auxtrace_cache__add(struct auxtrace_cache *c, u32 key,
			struct auxtrace_cache_entry *entry)
{
	if (c->limit && ++c->cnt > c->limit)
		auxtrace_cache__drop(c);

	entry->key = key;
	hlist_add_head(&entry->hash, &c->hashtable[hash_32(key, c->bits)]);

	return 0;
}