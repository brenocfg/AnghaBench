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
struct tc_device {char* id; struct tc_class* last_class; struct tc_class* classes; } ;
struct tc_class {char isqdisc; void* id; void* leafid; void* leaf_hash; void* parentid; void* parent_hash; void* hash; struct tc_class* prev; struct tc_class* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_TC_LOOP ; 
 struct tc_class* callocz (int,int) ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  error (char*,void*,char*) ; 
 scalar_t__ likely (struct tc_class*) ; 
 void* simple_hash (void*) ; 
 void* strdupz (char*) ; 
 struct tc_class* tc_class_index_add (struct tc_device*,struct tc_class*) ; 
 struct tc_class* tc_class_index_find (struct tc_device*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline struct tc_class *tc_class_add(struct tc_device *n, char *id, char qdisc, char *parentid, char *leafid)
{
    struct tc_class *c = tc_class_index_find(n, id, 0);

    if(!c) {
        debug(D_TC_LOOP, "TC: Creating in device '%s', class id '%s', parentid '%s', leafid '%s'", n->id, id, parentid?parentid:"", leafid?leafid:"");

        c = callocz(1, sizeof(struct tc_class));

        if(unlikely(!n->classes))
            n->classes = c;

        else if(likely(n->last_class)) {
            n->last_class->next = c;
            c->prev = n->last_class;
        }

        n->last_class = c;

        c->id = strdupz(id);
        c->hash = simple_hash(c->id);

        c->isqdisc = qdisc;
        if(parentid && *parentid) {
            c->parentid = strdupz(parentid);
            c->parent_hash = simple_hash(c->parentid);
        }

        if(leafid && *leafid) {
            c->leafid = strdupz(leafid);
            c->leaf_hash = simple_hash(c->leafid);
        }

        if(unlikely(tc_class_index_add(n, c) != c))
            error("plugin_tc: INTERNAL ERROR: attempt index class '%s' on device '%s': already exists", c->id, n->id);
    }
    return(c);
}