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
struct TYPE_3__ {int /*<<< orphan*/  desc; } ;
typedef  TYPE_1__ server_method ;
typedef  int /*<<< orphan*/  XMLRPC_VALUE ;
typedef  int /*<<< orphan*/  XMLRPC_SERVER ;

/* Variables and functions */
 int /*<<< orphan*/  XMLRPC_AddValueToVector (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* find_method (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static inline void describe_method(XMLRPC_SERVER server, XMLRPC_VALUE vector, const char* method) {
   if(method) {
      server_method* sm = find_method(server, method);
      if(sm) {
         XMLRPC_AddValueToVector(vector, sm->desc);
      }
   }
}