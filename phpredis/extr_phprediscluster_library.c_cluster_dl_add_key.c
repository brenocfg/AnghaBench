#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char* key; int key_len; int key_free; scalar_t__ val_free; scalar_t__ val_len; int /*<<< orphan*/ * val; } ;
typedef  TYPE_1__ clusterKeyVal ;
struct TYPE_8__ {size_t len; size_t size; TYPE_1__* entry; } ;
typedef  TYPE_2__ clusterDistList ;

/* Variables and functions */
 TYPE_1__* erealloc (TYPE_1__*,int) ; 

__attribute__((used)) static clusterKeyVal *cluster_dl_add_key(clusterDistList *dl, char *key,
                                         int key_len, int key_free)
{
    // Reallocate if required
    if (dl->len == dl->size) {
        dl->entry = erealloc(dl->entry, sizeof(clusterKeyVal) * dl->size * 2);
        dl->size *= 2;
    }

    // Set key info
    dl->entry[dl->len].key = key;
    dl->entry[dl->len].key_len = key_len;
    dl->entry[dl->len].key_free = key_free;

    // NULL out any values
    dl->entry[dl->len].val = NULL;
    dl->entry[dl->len].val_len = 0;
    dl->entry[dl->len].val_free = 0;

    return &(dl->entry[dl->len++]);
}