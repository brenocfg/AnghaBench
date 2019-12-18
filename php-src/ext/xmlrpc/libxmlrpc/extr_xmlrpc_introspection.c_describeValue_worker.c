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
typedef  int /*<<< orphan*/ * XMLRPC_VALUE ;

/* Variables and functions */
 int /*<<< orphan*/  XMLRPC_AddValueToVector (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * XMLRPC_CreateVector (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XMLRPC_VectorAppendInt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XMLRPC_VectorAppendString (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xi_token_default ; 
 int /*<<< orphan*/  xi_token_description ; 
 int /*<<< orphan*/  xi_token_name ; 
 int /*<<< orphan*/  xi_token_optional ; 
 int /*<<< orphan*/  xi_token_type ; 
 int /*<<< orphan*/  xmlrpc_vector_struct ; 

__attribute__((used)) static XMLRPC_VALUE describeValue_worker(const char* type, const char* id, const char* desc, int optional, const char* default_val, XMLRPC_VALUE sub_params) {
   XMLRPC_VALUE xParam = NULL;
   if(id || desc) {
      xParam = XMLRPC_CreateVector(NULL, xmlrpc_vector_struct);
      XMLRPC_VectorAppendString(xParam, xi_token_name, id, 0);
      XMLRPC_VectorAppendString(xParam, xi_token_type, type, 0);
      XMLRPC_VectorAppendString(xParam, xi_token_description, desc, 0);
      if(optional != 2) {
         XMLRPC_VectorAppendInt(xParam, xi_token_optional, optional);
      }
      if(optional == 1 && default_val) {
         XMLRPC_VectorAppendString(xParam, xi_token_default, default_val, 0);
      }
      XMLRPC_AddValueToVector(xParam, sub_params);
   }
   return xParam;
}