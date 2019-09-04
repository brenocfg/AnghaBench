#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_5__ {int /*<<< orphan*/  ldctl_oid; } ;
typedef  TYPE_1__ LDAPControl ;
typedef  int /*<<< orphan*/  LDAP ;

/* Variables and functions */
 int /*<<< orphan*/  _php_ldap_control_to_array (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  add_assoc_zval (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldap_controls_free (TYPE_1__**) ; 
 int /*<<< orphan*/ * zend_try_array_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void _php_ldap_controls_to_array(LDAP *ld, LDAPControl** ctrls, zval* array, int request)
{
	zval tmp1;
	LDAPControl **ctrlp;

	array = zend_try_array_init(array);
	if (!array) {
		return;
	}

	if (ctrls == NULL) {
		return;
	}
	ctrlp = ctrls;
	while (*ctrlp != NULL) {
		_php_ldap_control_to_array(ld, *ctrlp, &tmp1, request);
		add_assoc_zval(array, (*ctrlp)->ldctl_oid, &tmp1);
		ctrlp++;
	}
	ldap_controls_free(ctrls);
}