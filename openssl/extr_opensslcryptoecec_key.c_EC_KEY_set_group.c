#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * group; TYPE_1__* meth; } ;
struct TYPE_5__ {scalar_t__ (* set_group ) (TYPE_2__*,int /*<<< orphan*/  const*) ;} ;
typedef  TYPE_2__ EC_KEY ;
typedef  int /*<<< orphan*/  EC_GROUP ;

/* Variables and functions */
 int /*<<< orphan*/ * EC_GROUP_dup (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EC_GROUP_free (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (TYPE_2__*,int /*<<< orphan*/  const*) ; 

int EC_KEY_set_group(EC_KEY *key, const EC_GROUP *group)
{
    if (key->meth->set_group != NULL && key->meth->set_group(key, group) == 0)
        return 0;
    EC_GROUP_free(key->group);
    key->group = EC_GROUP_dup(group);
    return (key->group == NULL) ? 0 : 1;
}