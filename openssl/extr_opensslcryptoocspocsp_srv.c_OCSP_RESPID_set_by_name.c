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
typedef  int /*<<< orphan*/  X509 ;
struct TYPE_4__ {int /*<<< orphan*/  byName; } ;
struct TYPE_5__ {int /*<<< orphan*/  type; TYPE_1__ value; } ;
typedef  TYPE_2__ OCSP_RESPID ;

/* Variables and functions */
 int /*<<< orphan*/  V_OCSP_RESPID_NAME ; 
 int /*<<< orphan*/  X509_NAME_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  X509_get_subject_name (int /*<<< orphan*/ *) ; 

int OCSP_RESPID_set_by_name(OCSP_RESPID *respid, X509 *cert)
{
    if (!X509_NAME_set(&respid->value.byName, X509_get_subject_name(cert)))
        return 0;

    respid->type = V_OCSP_RESPID_NAME;

    return 1;
}