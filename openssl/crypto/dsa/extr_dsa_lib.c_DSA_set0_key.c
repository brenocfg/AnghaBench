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
struct TYPE_3__ {int /*<<< orphan*/  dirty_cnt; int /*<<< orphan*/ * priv_key; int /*<<< orphan*/ * pub_key; } ;
typedef  TYPE_1__ DSA ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 

int DSA_set0_key(DSA *d, BIGNUM *pub_key, BIGNUM *priv_key)
{
    /* If the field pub_key in d is NULL, the corresponding input
     * parameters MUST be non-NULL.  The priv_key field may
     * be left NULL.
     */
    if (d->pub_key == NULL && pub_key == NULL)
        return 0;

    if (pub_key != NULL) {
        BN_free(d->pub_key);
        d->pub_key = pub_key;
    }
    if (priv_key != NULL) {
        BN_free(d->priv_key);
        d->priv_key = priv_key;
    }
    d->dirty_cnt++;

    return 1;
}