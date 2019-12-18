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
struct TYPE_3__ {int /*<<< orphan*/  type; int /*<<< orphan*/  str; } ;

/* Variables and functions */
 int /*<<< orphan*/  simplestring_add (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  simplestring_addn (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  simplestring_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlrpc_base64 ; 

void XMLRPC_SetValueBase64(XMLRPC_VALUE value, const char* s, int len) {
   if(value && s) {
      simplestring_clear(&value->str);
      (len > 0) ? simplestring_addn(&value->str, s, len) :
                  simplestring_add(&value->str, s);
      value->type = xmlrpc_base64;
   }
}