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
typedef  int /*<<< orphan*/  time_t ;
typedef  TYPE_1__* XMLRPC_VALUE ;
struct TYPE_3__ {int /*<<< orphan*/  str; int /*<<< orphan*/  i; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  date_from_ISO8601 (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simplestring_add (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  simplestring_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlrpc_datetime ; 

void XMLRPC_SetValueDateTime_ISO8601(XMLRPC_VALUE value, const char* s) {
   if(value) {
      time_t time_val = 0;
      if(s) {
         value->type = xmlrpc_datetime;
         date_from_ISO8601(s, &time_val);
         value->i = time_val;
         simplestring_clear(&value->str);
         simplestring_add(&value->str, s);
      }
   }
}