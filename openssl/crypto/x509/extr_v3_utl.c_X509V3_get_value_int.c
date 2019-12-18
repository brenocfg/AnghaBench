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
struct TYPE_4__ {int /*<<< orphan*/  value; } ;
typedef  TYPE_1__ CONF_VALUE ;
typedef  int /*<<< orphan*/  ASN1_INTEGER ;

/* Variables and functions */
 int /*<<< orphan*/  X509V3_conf_err (TYPE_1__ const*) ; 
 int /*<<< orphan*/ * s2i_ASN1_INTEGER (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int X509V3_get_value_int(const CONF_VALUE *value, ASN1_INTEGER **aint)
{
    ASN1_INTEGER *itmp;

    if ((itmp = s2i_ASN1_INTEGER(NULL, value->value)) == NULL) {
        X509V3_conf_err(value);
        return 0;
    }
    *aint = itmp;
    return 1;
}