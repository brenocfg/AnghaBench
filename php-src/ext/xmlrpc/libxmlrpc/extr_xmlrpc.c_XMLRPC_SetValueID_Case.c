#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* XMLRPC_VALUE ;
typedef  scalar_t__ XMLRPC_CASE ;
struct TYPE_7__ {int len; char* str; } ;
struct TYPE_6__ {TYPE_2__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,char const*) ; 
 int /*<<< orphan*/  simplestring_add (TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  simplestring_addn (TYPE_2__*,char const*,int) ; 
 int /*<<< orphan*/  simplestring_clear (TYPE_2__*) ; 
 char tolower (char) ; 
 char toupper (char) ; 
 scalar_t__ xmlrpc_case_lower ; 
 scalar_t__ xmlrpc_case_upper ; 

const char *XMLRPC_SetValueID_Case(XMLRPC_VALUE value, const char* id, int len, XMLRPC_CASE id_case) {
   const char* pRetval = NULL;
   if(value) {
      if(id) {
         simplestring_clear(&value->id);
         (len > 0) ? simplestring_addn(&value->id, id, len) :
                     simplestring_add(&value->id, id);

         /* upper or lower case string in place if required. could be a separate func. */
         if(id_case == xmlrpc_case_lower || id_case == xmlrpc_case_upper) {
            int i;
            for(i = 0; i < value->id.len; i++) {
					value->id.str[i] =
					(id_case ==
					 xmlrpc_case_lower) ? tolower (value->id.
															 str[i]) : toupper (value->
																					  id.
																					  str[i]);
            }
         }

         pRetval = value->id.str;

#ifdef XMLRPC_DEBUG_REFCOUNT
         printf("set value id: %s\n", pRetval);
#endif
      }
   }

   return pRetval;
}