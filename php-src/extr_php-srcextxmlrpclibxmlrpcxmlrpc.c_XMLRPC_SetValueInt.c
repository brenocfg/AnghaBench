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
typedef  TYPE_1__* XMLRPC_VALUE ;
struct TYPE_3__ {int i; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  xmlrpc_int ; 

void XMLRPC_SetValueInt(XMLRPC_VALUE value, int val) {
   if(value) {
      value->type = xmlrpc_int;
      value->i = val;
   }
}