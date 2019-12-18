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
struct TYPE_3__ {int /*<<< orphan*/  attrib; } ;
typedef  TYPE_1__ PKCS12_SAFEBAG ;

/* Variables and functions */
 int /*<<< orphan*/  MBSTRING_UTF8 ; 
 int /*<<< orphan*/  NID_friendlyName ; 
 scalar_t__ X509at_add1_attr_by_NID (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int) ; 

int PKCS12_add_friendlyname_utf8(PKCS12_SAFEBAG *bag, const char *name,
                                int namelen)
{
    if (X509at_add1_attr_by_NID(&bag->attrib, NID_friendlyName,
                                MBSTRING_UTF8, (unsigned char *)name, namelen))
        return 1;
    else
        return 0;
}