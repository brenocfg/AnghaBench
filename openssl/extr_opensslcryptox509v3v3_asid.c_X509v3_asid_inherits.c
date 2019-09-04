#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* rdi; TYPE_1__* asnum; } ;
struct TYPE_6__ {scalar_t__ type; } ;
struct TYPE_5__ {scalar_t__ type; } ;
typedef  TYPE_3__ ASIdentifiers ;

/* Variables and functions */
 scalar_t__ ASIdentifierChoice_inherit ; 

int X509v3_asid_inherits(ASIdentifiers *asid)
{
    return (asid != NULL &&
            ((asid->asnum != NULL &&
              asid->asnum->type == ASIdentifierChoice_inherit) ||
             (asid->rdi != NULL &&
              asid->rdi->type == ASIdentifierChoice_inherit)));
}