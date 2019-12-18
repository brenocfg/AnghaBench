#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/ * priv_key; TYPE_2__* meth; TYPE_3__* group; } ;
struct TYPE_10__ {TYPE_1__* meth; } ;
struct TYPE_9__ {scalar_t__ (* set_private ) (TYPE_4__*,int /*<<< orphan*/  const*) ;} ;
struct TYPE_8__ {scalar_t__ (* set_private ) (TYPE_4__*,int /*<<< orphan*/  const*) ;} ;
typedef  TYPE_4__ EC_KEY ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_clear_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_dup (int /*<<< orphan*/  const*) ; 
 scalar_t__ stub1 (TYPE_4__*,int /*<<< orphan*/  const*) ; 
 scalar_t__ stub2 (TYPE_4__*,int /*<<< orphan*/  const*) ; 

int EC_KEY_set_private_key(EC_KEY *key, const BIGNUM *priv_key)
{
    if (key->group == NULL || key->group->meth == NULL)
        return 0;
    if (key->group->meth->set_private != NULL
        && key->group->meth->set_private(key, priv_key) == 0)
        return 0;
    if (key->meth->set_private != NULL
        && key->meth->set_private(key, priv_key) == 0)
        return 0;
    BN_clear_free(key->priv_key);
    key->priv_key = BN_dup(priv_key);
    return (key->priv_key == NULL) ? 0 : 1;
}