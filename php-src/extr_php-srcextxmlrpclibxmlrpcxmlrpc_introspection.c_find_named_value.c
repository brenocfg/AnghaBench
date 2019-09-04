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
 char* XMLRPC_VectorGetStringWithID (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * XMLRPC_VectorNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * XMLRPC_VectorRewind (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (char const*,char const*) ; 
 int /*<<< orphan*/  xi_token_name ; 

__attribute__((used)) static inline XMLRPC_VALUE find_named_value(XMLRPC_VALUE list, const char* needle) {
   XMLRPC_VALUE xIter = XMLRPC_VectorRewind(list);
   while(xIter) {
      const char* name = XMLRPC_VectorGetStringWithID(xIter, xi_token_name);
      if(name && !strcmp(name, needle)) {
         return xIter;
      }
      xIter = XMLRPC_VectorNext(list);
   }
   return NULL;
}