#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X509_SIG ;
struct TYPE_4__ {int /*<<< orphan*/  const* shkeybag; } ;
struct TYPE_5__ {TYPE_1__ value; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ PKCS12_SAFEBAG ;

/* Variables and functions */
 scalar_t__ NID_pkcs8ShroudedKeyBag ; 
 scalar_t__ OBJ_obj2nid (int /*<<< orphan*/ ) ; 

const X509_SIG *PKCS12_SAFEBAG_get0_pkcs8(const PKCS12_SAFEBAG *bag)
{
    if (OBJ_obj2nid(bag->type) != NID_pkcs8ShroudedKeyBag)
        return NULL;
    return bag->value.shkeybag;
}