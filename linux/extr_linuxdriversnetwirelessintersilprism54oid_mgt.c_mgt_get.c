#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ ** mib; } ;
typedef  TYPE_1__ islpci_private ;
typedef  enum oid_num_t { ____Placeholder_oid_num_t } oid_num_t ;
struct TYPE_5__ {int flags; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int OID_FLAG_TYPE ; 
 int OID_NUM_LAST ; 
 TYPE_3__* isl_oid ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mgt_le_to_cpu (int,void*) ; 

void
mgt_get(islpci_private *priv, enum oid_num_t n, void *res)
{
	BUG_ON(n >= OID_NUM_LAST);
	BUG_ON(priv->mib[n] == NULL);
	BUG_ON(res == NULL);

	memcpy(res, priv->mib[n], isl_oid[n].size);
	mgt_le_to_cpu(isl_oid[n].flags & OID_FLAG_TYPE, res);
}