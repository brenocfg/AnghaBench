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
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_string ;
typedef  TYPE_1__* soapServicePtr ;
typedef  int /*<<< orphan*/  sdlFunctionPtr ;
struct TYPE_3__ {scalar_t__ send_errors; } ;

/* Variables and functions */
 int /*<<< orphan*/  EG (int /*<<< orphan*/ ) ; 
 char* ZSTR_VAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_OBJ (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Z_OBJCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_soap_fault_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exception ; 
 scalar_t__ instanceof_function (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  soap_fault_class_entry ; 
 int /*<<< orphan*/  soap_server_fault_ex (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_ce_error ; 
 int /*<<< orphan*/  zend_read_property (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_string_release_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zval_get_string (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _soap_server_exception(soapServicePtr service, sdlFunctionPtr function, zval *this_ptr) /* {{{ */
{
	zval exception_object;

	ZVAL_OBJ(&exception_object, EG(exception));
	if (instanceof_function(Z_OBJCE(exception_object), soap_fault_class_entry)) {
		soap_server_fault_ex(function, &exception_object, NULL);
	} else if (instanceof_function(Z_OBJCE(exception_object), zend_ce_error)) {
		if (service->send_errors) {
			zval rv;
			zend_string *msg = zval_get_string(zend_read_property(zend_ce_error, &exception_object, "message", sizeof("message")-1, 0, &rv));
			add_soap_fault_ex(&exception_object, this_ptr, "Server", ZSTR_VAL(msg), NULL, NULL);
			zend_string_release_ex(msg, 0);
		} else {
			add_soap_fault_ex(&exception_object, this_ptr, "Server", "Internal Error", NULL, NULL);
		}
		soap_server_fault_ex(function, &exception_object, NULL);
	}
}