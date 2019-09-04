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
typedef  int /*<<< orphan*/  ASN1_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/ * OBJ_txt2obj (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_err ; 

__attribute__((used)) static ASN1_OBJECT *txt2obj(const char *oid)
{
    ASN1_OBJECT *oid_obj = NULL;

    if ((oid_obj = OBJ_txt2obj(oid, 0)) == NULL)
        BIO_printf(bio_err, "cannot convert %s to OID\n", oid);

    return oid_obj;
}