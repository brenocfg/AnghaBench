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
typedef  TYPE_1__* xmlNsPtr ;
typedef  int /*<<< orphan*/  xmlNodePtr ;
typedef  int /*<<< orphan*/  smart_str ;
struct TYPE_3__ {scalar_t__ prefix; } ;

/* Variables and functions */
 scalar_t__ SOAP_1_1 ; 
 char* SOAP_1_1_ENC_NAMESPACE ; 
 scalar_t__ SOAP_1_2 ; 
 char* SOAP_1_2_ENC_NAMESPACE ; 
 scalar_t__ SOAP_GLOBAL (int /*<<< orphan*/ ) ; 
 TYPE_1__* encode_add_ns (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  smart_str_0 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smart_str_appendc (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  smart_str_appendl (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smart_str_appends (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  soap_version ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static void get_type_str(xmlNodePtr node, const char* ns, const char* type, smart_str* ret)
{

	if (ns) {
		xmlNsPtr xmlns;
		if (SOAP_GLOBAL(soap_version) == SOAP_1_2 &&
		    strcmp(ns,SOAP_1_1_ENC_NAMESPACE) == 0) {
			ns = SOAP_1_2_ENC_NAMESPACE;
		} else if (SOAP_GLOBAL(soap_version) == SOAP_1_1 &&
		           strcmp(ns,SOAP_1_2_ENC_NAMESPACE) == 0) {
			ns = SOAP_1_1_ENC_NAMESPACE;
		}
		xmlns = encode_add_ns(node, ns);
		smart_str_appends(ret, (char*)xmlns->prefix);
		smart_str_appendc(ret, ':');
	}
	smart_str_appendl(ret, type, strlen(type));
	smart_str_0(ret);
}