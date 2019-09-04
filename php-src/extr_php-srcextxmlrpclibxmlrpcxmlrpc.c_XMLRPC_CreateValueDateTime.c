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
typedef  int /*<<< orphan*/  time_t ;
typedef  scalar_t__ XMLRPC_VALUE ;

/* Variables and functions */
 scalar_t__ XMLRPC_CreateValueEmpty () ; 
 int /*<<< orphan*/  XMLRPC_SetValueDateTime (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XMLRPC_SetValueID (scalar_t__,char const*,int /*<<< orphan*/ ) ; 

XMLRPC_VALUE XMLRPC_CreateValueDateTime(const char* id, time_t time) {
   XMLRPC_VALUE val = XMLRPC_CreateValueEmpty();
   if(val) {
      XMLRPC_SetValueDateTime(val, time);
      if(id) {
         XMLRPC_SetValueID(val, id, 0);
      }
   }
   return val;
}