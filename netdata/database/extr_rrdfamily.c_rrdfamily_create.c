#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char* family; int /*<<< orphan*/  use_count; int /*<<< orphan*/  rrdvar_root_index; int /*<<< orphan*/  hash_family; } ;
typedef  int /*<<< orphan*/  RRDHOST ;
typedef  TYPE_1__ RRDFAMILY ;

/* Variables and functions */
 int /*<<< orphan*/  avl_init_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* callocz (int,int) ; 
 int /*<<< orphan*/  error (char*,char*,char*) ; 
 TYPE_1__* rrdfamily_index_add (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* rrdfamily_index_find (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrdvar_compare ; 
 int /*<<< orphan*/  simple_hash (char*) ; 
 char* strdupz (char const*) ; 

RRDFAMILY *rrdfamily_create(RRDHOST *host, const char *id) {
    RRDFAMILY *rc = rrdfamily_index_find(host, id, 0);
    if(!rc) {
        rc = callocz(1, sizeof(RRDFAMILY));

        rc->family = strdupz(id);
        rc->hash_family = simple_hash(rc->family);

        // initialize the variables index
        avl_init_lock(&rc->rrdvar_root_index, rrdvar_compare);

        RRDFAMILY *ret = rrdfamily_index_add(host, rc);
        if(ret != rc)
            error("RRDFAMILY: INTERNAL ERROR: Expected to INSERT RRDFAMILY '%s' into index, but inserted '%s'.", rc->family, (ret)?ret->family:"NONE");
    }

    rc->use_count++;
    return rc;
}