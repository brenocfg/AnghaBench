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
typedef  TYPE_1__* xmlNodePtr ;
struct TYPE_5__ {scalar_t__ type; struct TYPE_5__* next; } ;
typedef  void* SOAP_GLOBAL ;

/* Variables and functions */
 void* SOAP_1_1 ; 
 char* SOAP_1_1_ENV_NAMESPACE ; 
 void* SOAP_1_2 ; 
 char* SOAP_1_2_ENV_NAMESPACE ; 
 scalar_t__ XML_ELEMENT_NODE ; 
 scalar_t__ node_is_equal_ex (TYPE_1__*,char*,char*) ; 
 int /*<<< orphan*/  soap_server_fault (char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static xmlNodePtr get_envelope(xmlNodePtr trav, int *version, char **envelope_ns) {
	while (trav != NULL) {
		if (trav->type == XML_ELEMENT_NODE) {
			if (node_is_equal_ex(trav,"Envelope",SOAP_1_1_ENV_NAMESPACE)) {
				*version = SOAP_1_1;
				*envelope_ns = SOAP_1_1_ENV_NAMESPACE;
				SOAP_GLOBAL(soap_version) = SOAP_1_1;
				return trav;
			}

			if (node_is_equal_ex(trav,"Envelope",SOAP_1_2_ENV_NAMESPACE)) {
				*version = SOAP_1_2;
				*envelope_ns = SOAP_1_2_ENV_NAMESPACE;
				SOAP_GLOBAL(soap_version) = SOAP_1_2;
				return trav;
			}

			soap_server_fault("VersionMismatch", "Wrong Version", NULL, NULL, NULL);
		}
		trav = trav->next;
	}

	return NULL;
}