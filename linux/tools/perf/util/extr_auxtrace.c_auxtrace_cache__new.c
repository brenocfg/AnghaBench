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
struct hlist_head {int dummy; } ;
struct auxtrace_cache {size_t sz; size_t entry_size; unsigned int limit; unsigned int bits; struct hlist_head* hashtable; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_HLIST_HEAD (struct hlist_head*) ; 
 struct hlist_head* calloc (size_t,int) ; 
 int /*<<< orphan*/  free (struct auxtrace_cache*) ; 
 struct auxtrace_cache* zalloc (int) ; 

struct auxtrace_cache *auxtrace_cache__new(unsigned int bits, size_t entry_size,
					   unsigned int limit_percent)
{
	struct auxtrace_cache *c;
	struct hlist_head *ht;
	size_t sz, i;

	c = zalloc(sizeof(struct auxtrace_cache));
	if (!c)
		return NULL;

	sz = 1UL << bits;

	ht = calloc(sz, sizeof(struct hlist_head));
	if (!ht)
		goto out_free;

	for (i = 0; i < sz; i++)
		INIT_HLIST_HEAD(&ht[i]);

	c->hashtable = ht;
	c->sz = sz;
	c->entry_size = entry_size;
	c->limit = (c->sz * limit_percent) / 100;
	c->bits = bits;

	return c;

out_free:
	free(c);
	return NULL;
}