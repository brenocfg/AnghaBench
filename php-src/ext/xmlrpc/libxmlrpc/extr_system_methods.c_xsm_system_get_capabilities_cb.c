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
typedef  int /*<<< orphan*/  XMLRPC_VALUE ;
typedef  int /*<<< orphan*/  XMLRPC_SERVER ;
typedef  int /*<<< orphan*/  XMLRPC_REQUEST ;

/* Variables and functions */
 int /*<<< orphan*/  XMLRPC_AddValuesToVector (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XMLRPC_CreateVector (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XMLRPC_VectorAppendInt (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  XMLRPC_VectorAppendString (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlrpc_vector_struct ; 

XMLRPC_VALUE xsm_system_get_capabilities_cb(XMLRPC_SERVER server, XMLRPC_REQUEST input, void* userData) {
   XMLRPC_VALUE xReturn = XMLRPC_CreateVector(0, xmlrpc_vector_struct);
   XMLRPC_VALUE xFaults = XMLRPC_CreateVector("faults_interop", xmlrpc_vector_struct);
   XMLRPC_VALUE xIntro = XMLRPC_CreateVector("introspection", xmlrpc_vector_struct);

   /* support for fault spec */
   XMLRPC_VectorAppendString(xFaults, "specURL", "http://xmlrpc-epi.sourceforge.net/specs/rfc.fault_codes.php", 0);
   XMLRPC_VectorAppendInt(xFaults, "specVersion", 20010516);

   /* support for introspection spec */
   XMLRPC_VectorAppendString(xIntro, "specURL", "http://xmlrpc-epi.sourceforge.net/specs/rfc.introspection.php", 0);
   XMLRPC_VectorAppendInt(xIntro, "specVersion", 20010516);

   XMLRPC_AddValuesToVector(xReturn,
                            xFaults,
                            xIntro,
                            NULL);

   return xReturn;

}