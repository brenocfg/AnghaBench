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
struct TYPE_3__ {int /*<<< orphan*/  unauth_attr; } ;
typedef  TYPE_1__ PKCS7_SIGNER_INFO ;

/* Variables and functions */
 int add_attribute (int /*<<< orphan*/ *,int,int,void*) ; 

int PKCS7_add_attribute(PKCS7_SIGNER_INFO *p7si, int nid, int atrtype,
                        void *value)
{
    return add_attribute(&(p7si->unauth_attr), nid, atrtype, value);
}