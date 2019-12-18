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
struct errormap {int /*<<< orphan*/  list; int /*<<< orphan*/  namelen; int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int ERRHASHSZ ; 
 int /*<<< orphan*/  INIT_HLIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_HLIST_NODE (int /*<<< orphan*/ *) ; 
 struct errormap* errmap ; 
 int /*<<< orphan*/ * hash_errmap ; 
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int jhash (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ *) ; 

int p9_error_init(void)
{
	struct errormap *c;
	int bucket;

	/* initialize hash table */
	for (bucket = 0; bucket < ERRHASHSZ; bucket++)
		INIT_HLIST_HEAD(&hash_errmap[bucket]);

	/* load initial error map into hash table */
	for (c = errmap; c->name != NULL; c++) {
		c->namelen = strlen(c->name);
		bucket = jhash(c->name, c->namelen, 0) % ERRHASHSZ;
		INIT_HLIST_NODE(&c->list);
		hlist_add_head(&c->list, &hash_errmap[bucket]);
	}

	return 1;
}