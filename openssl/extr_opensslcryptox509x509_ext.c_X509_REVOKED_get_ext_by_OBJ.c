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
struct TYPE_3__ {int /*<<< orphan*/  extensions; } ;
typedef  TYPE_1__ X509_REVOKED ;
typedef  int /*<<< orphan*/  ASN1_OBJECT ;

/* Variables and functions */
 int X509v3_get_ext_by_OBJ (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 

int X509_REVOKED_get_ext_by_OBJ(const X509_REVOKED *x, const ASN1_OBJECT *obj,
                                int lastpos)
{
    return X509v3_get_ext_by_OBJ(x->extensions, obj, lastpos);
}