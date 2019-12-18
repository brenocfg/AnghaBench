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
typedef  int /*<<< orphan*/  X509_ATTRIBUTE ;
struct TYPE_3__ {int /*<<< orphan*/  attrib; } ;
typedef  TYPE_1__ PKCS12_SAFEBAG ;
typedef  int /*<<< orphan*/  EVP_PKEY ;

/* Variables and functions */
 int /*<<< orphan*/ * EVP_PKEY_get_attr (int /*<<< orphan*/ *,int) ; 
 int EVP_PKEY_get_attr_by_NID (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  X509at_add1_attr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int copy_bag_attr(PKCS12_SAFEBAG *bag, EVP_PKEY *pkey, int nid)
{
    int idx;
    X509_ATTRIBUTE *attr;
    idx = EVP_PKEY_get_attr_by_NID(pkey, nid, -1);
    if (idx < 0)
        return 1;
    attr = EVP_PKEY_get_attr(pkey, idx);
    if (!X509at_add1_attr(&bag->attrib, attr))
        return 0;
    return 1;
}