#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ ptr; } ;
typedef  TYPE_1__ zend_resource ;
struct TYPE_6__ {int /*<<< orphan*/  res; int /*<<< orphan*/ * ber; } ;
typedef  TYPE_2__ ldap_resultentry ;

/* Variables and functions */
 int /*<<< orphan*/  ber_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efree (TYPE_2__*) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void _free_ldap_result_entry(zend_resource *rsrc) /* {{{ */
{
	ldap_resultentry *entry = (ldap_resultentry *)rsrc->ptr;

	if (entry->ber != NULL) {
		ber_free(entry->ber, 0);
		entry->ber = NULL;
	}
	zval_ptr_dtor(&entry->res);
	efree(entry);
}