#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_3__ {int len; struct TYPE_3__* entry; struct TYPE_3__* val; scalar_t__ val_free; struct TYPE_3__* key; scalar_t__ key_free; } ;
typedef  TYPE_1__ clusterDistList ;

/* Variables and functions */
 int /*<<< orphan*/  efree (TYPE_1__*) ; 

__attribute__((used)) static void cluster_dist_free_ht(zval *p) {
    clusterDistList *dl = *(clusterDistList**)p;
    int i;

    for (i = 0; i < dl->len; i++) {
        if (dl->entry[i].key_free)
            efree(dl->entry[i].key);
        if (dl->entry[i].val_free)
            efree(dl->entry[i].val);
    }

    efree(dl->entry);
    efree(dl);
}