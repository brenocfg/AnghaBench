#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* XMLRPC_REQUEST ;
struct TYPE_6__ {char const* str; } ;
struct TYPE_5__ {TYPE_2__ methodName; } ;

/* Variables and functions */
 int /*<<< orphan*/  simplestring_add (TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  simplestring_clear (TYPE_2__*) ; 

const char* XMLRPC_RequestSetMethodName(XMLRPC_REQUEST request, const char* methodName) {
   if(request) {
      simplestring_clear(&request->methodName);
      simplestring_add(&request->methodName, methodName);
      return request->methodName.str;
   }
   return NULL;
}