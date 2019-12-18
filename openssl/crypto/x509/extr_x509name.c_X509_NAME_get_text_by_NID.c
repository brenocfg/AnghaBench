#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  X509_NAME ;
typedef  int /*<<< orphan*/  ASN1_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/ * OBJ_nid2obj (int) ; 
 int X509_NAME_get_text_by_OBJ (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int) ; 

int X509_NAME_get_text_by_NID(X509_NAME *name, int nid, char *buf, int len)
{
    ASN1_OBJECT *obj;

    obj = OBJ_nid2obj(nid);
    if (obj == NULL)
        return -1;
    return X509_NAME_get_text_by_OBJ(name, obj, buf, len);
}