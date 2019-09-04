#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int (* check_trust ) (TYPE_1__*,int /*<<< orphan*/ *,int) ;} ;
typedef  TYPE_1__ X509_TRUST ;
typedef  int /*<<< orphan*/  X509 ;

/* Variables and functions */
 int /*<<< orphan*/  NID_anyExtendedKeyUsage ; 
 int X509_TRUST_DEFAULT ; 
 int X509_TRUST_DO_SS_COMPAT ; 
 TYPE_1__* X509_TRUST_get0 (int) ; 
 int X509_TRUST_get_by_id (int) ; 
 int default_trust (int,int /*<<< orphan*/ *,int) ; 
 int obj_trust (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int stub1 (TYPE_1__*,int /*<<< orphan*/ *,int) ; 

int X509_check_trust(X509 *x, int id, int flags)
{
    X509_TRUST *pt;
    int idx;

    /* We get this as a default value */
    if (id == X509_TRUST_DEFAULT)
        return obj_trust(NID_anyExtendedKeyUsage, x,
                         flags | X509_TRUST_DO_SS_COMPAT);
    idx = X509_TRUST_get_by_id(id);
    if (idx == -1)
        return default_trust(id, x, flags);
    pt = X509_TRUST_get0(idx);
    return pt->check_trust(pt, x, flags);
}