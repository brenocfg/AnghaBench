#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int up_load; int num_items; int num_nodes; int /*<<< orphan*/  num_replace; int /*<<< orphan*/  num_insert; scalar_t__ error; } ;
struct TYPE_8__ {unsigned long hash; void* data; int /*<<< orphan*/ * next; } ;
typedef  TYPE_1__ OPENSSL_LH_NODE ;
typedef  TYPE_2__ OPENSSL_LHASH ;

/* Variables and functions */
 int LH_LOAD_MULT ; 
 TYPE_1__* OPENSSL_malloc (int) ; 
 int /*<<< orphan*/  expand (TYPE_2__*) ; 
 TYPE_1__** getrn (TYPE_2__*,void*,unsigned long*) ; 

void *OPENSSL_LH_insert(OPENSSL_LHASH *lh, void *data)
{
    unsigned long hash;
    OPENSSL_LH_NODE *nn, **rn;
    void *ret;

    lh->error = 0;
    if ((lh->up_load <= (lh->num_items * LH_LOAD_MULT / lh->num_nodes)) && !expand(lh))
        return NULL;        /* 'lh->error++' already done in 'expand' */

    rn = getrn(lh, data, &hash);

    if (*rn == NULL) {
        if ((nn = OPENSSL_malloc(sizeof(*nn))) == NULL) {
            lh->error++;
            return NULL;
        }
        nn->data = data;
        nn->next = NULL;
        nn->hash = hash;
        *rn = nn;
        ret = NULL;
        lh->num_insert++;
        lh->num_items++;
    } else {                    /* replace same key */
        ret = (*rn)->data;
        (*rn)->data = data;
        lh->num_replace++;
    }
    return ret;
}