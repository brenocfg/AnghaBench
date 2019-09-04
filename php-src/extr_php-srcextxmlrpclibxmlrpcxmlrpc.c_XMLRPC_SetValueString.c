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
struct TYPE_7__ {scalar_t__ str; } ;
struct TYPE_6__ {TYPE_2__ str; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  simplestring_add (TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  simplestring_addn (TYPE_2__*,char const*,int) ; 
 int /*<<< orphan*/  simplestring_clear (TYPE_2__*) ; 
 int /*<<< orphan*/  xmlrpc_string ; 

const char *XMLRPC_SetValueString(XMLRPC_VALUE value, const char* val, int len) {
   char *pRetval = NULL;
   if(value && val) {
      simplestring_clear(&value->str);
      (len > 0) ? simplestring_addn(&value->str, val, len) :
                  simplestring_add(&value->str, val);
      value->type = xmlrpc_string;
      pRetval = (char *)value->str.str;
   }

   return pRetval;
}