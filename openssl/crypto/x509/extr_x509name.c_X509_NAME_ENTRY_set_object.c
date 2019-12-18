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
struct TYPE_3__ {int /*<<< orphan*/ * object; } ;
typedef  TYPE_1__ X509_NAME_ENTRY ;
typedef  int /*<<< orphan*/  ASN1_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_OBJECT_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR_R_PASSED_NULL_PARAMETER ; 
 int /*<<< orphan*/ * OBJ_dup (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  X509_F_X509_NAME_ENTRY_SET_OBJECT ; 
 int /*<<< orphan*/  X509err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int X509_NAME_ENTRY_set_object(X509_NAME_ENTRY *ne, const ASN1_OBJECT *obj)
{
    if ((ne == NULL) || (obj == NULL)) {
        X509err(X509_F_X509_NAME_ENTRY_SET_OBJECT,
                ERR_R_PASSED_NULL_PARAMETER);
        return 0;
    }
    ASN1_OBJECT_free(ne->object);
    ne->object = OBJ_dup(obj);
    return ((ne->object == NULL) ? 0 : 1);
}