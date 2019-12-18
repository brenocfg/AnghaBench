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
typedef  int /*<<< orphan*/  XMLRPC_VECTOR_TYPE ;
typedef  int /*<<< orphan*/ * XMLRPC_VALUE ;

/* Variables and functions */
 int /*<<< orphan*/ * XMLRPC_CreateValueEmpty () ; 
 scalar_t__ XMLRPC_SetIsVector (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* XMLRPC_SetValueID (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 

XMLRPC_VALUE XMLRPC_CreateVector(const char* id, XMLRPC_VECTOR_TYPE type) {
   XMLRPC_VALUE val = NULL;

   val = XMLRPC_CreateValueEmpty();
   if(val) {
      if(XMLRPC_SetIsVector(val, type)) {
         if(id) {
            const char *pSVI = NULL;

            pSVI = XMLRPC_SetValueID(val, id, 0);
            if(NULL == pSVI) {
               val = NULL;
            }
         }
      }
      else {
         val = NULL;
      }
   }
   return val;
}