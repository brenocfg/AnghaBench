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
typedef  int /*<<< orphan*/  zval ;

/* Variables and functions */
 scalar_t__ IS_OBJECT ; 
 scalar_t__ IS_UNDEF ; 
 int SOAP_1_1 ; 
 char* SOAP_1_1_ENV_NAMESPACE ; 
 int SOAP_1_2 ; 
 char* SOAP_1_2_ENV_NAMESPACE ; 
 int SOAP_GLOBAL (int /*<<< orphan*/ ) ; 
 scalar_t__ Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_property_string (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  add_property_zval (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  object_init_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  soap_fault_class_entry ; 
 int soap_version ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  zend_ce_exception ; 
 int /*<<< orphan*/  zend_update_property_string (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int,char*) ; 

__attribute__((used)) static void set_soap_fault(zval *obj, char *fault_code_ns, char *fault_code, char *fault_string, char *fault_actor, zval *fault_detail, char *name) /* {{{ */
{
	if (Z_TYPE_P(obj) != IS_OBJECT) {
		object_init_ex(obj, soap_fault_class_entry);
	}

	add_property_string(obj, "faultstring", fault_string ? fault_string : "");
	zend_update_property_string(zend_ce_exception, obj, "message", sizeof("message")-1, (fault_string ? fault_string : ""));

	if (fault_code != NULL) {
		int soap_version = SOAP_GLOBAL(soap_version);

		if (fault_code_ns) {
			add_property_string(obj, "faultcode", fault_code);
			add_property_string(obj, "faultcodens", fault_code_ns);
		} else {
			if (soap_version == SOAP_1_1) {
				add_property_string(obj, "faultcode", fault_code);
				if (strcmp(fault_code,"Client") == 0 ||
				    strcmp(fault_code,"Server") == 0 ||
				    strcmp(fault_code,"VersionMismatch") == 0 ||
			  	  strcmp(fault_code,"MustUnderstand") == 0) {
					add_property_string(obj, "faultcodens", SOAP_1_1_ENV_NAMESPACE);
				}
			} else if (soap_version == SOAP_1_2) {
				if (strcmp(fault_code,"Client") == 0) {
					add_property_string(obj, "faultcode", "Sender");
					add_property_string(obj, "faultcodens", SOAP_1_2_ENV_NAMESPACE);
				} else if (strcmp(fault_code,"Server") == 0) {
					add_property_string(obj, "faultcode", "Receiver");
					add_property_string(obj, "faultcodens", SOAP_1_2_ENV_NAMESPACE);
				} else if (strcmp(fault_code,"VersionMismatch") == 0 ||
				           strcmp(fault_code,"MustUnderstand") == 0 ||
				           strcmp(fault_code,"DataEncodingUnknown") == 0) {
					add_property_string(obj, "faultcode", fault_code);
					add_property_string(obj, "faultcodens", SOAP_1_2_ENV_NAMESPACE);
				} else {
					add_property_string(obj, "faultcode", fault_code);
				}
			}
		}
	}
	if (fault_actor != NULL) {
		add_property_string(obj, "faultactor", fault_actor);
	}
	if (fault_detail != NULL && Z_TYPE_P(fault_detail) != IS_UNDEF) {
		add_property_zval(obj, "detail", fault_detail);
	}
	if (name != NULL) {
		add_property_string(obj, "_name", name);
	}
}