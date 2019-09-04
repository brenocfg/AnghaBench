#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* XMLRPC_VALUE ;
struct TYPE_4__ {int /*<<< orphan*/  str; int /*<<< orphan*/  id; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  STRUCT_XMLRPC_VALUE ;

/* Variables and functions */
 TYPE_1__* ecalloc (int,int) ; 
 int /*<<< orphan*/  simplestring_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlrpc_empty ; 

XMLRPC_VALUE XMLRPC_CreateValueEmpty() {
   XMLRPC_VALUE v = ecalloc(1, sizeof(STRUCT_XMLRPC_VALUE));
   if(v) {
#ifdef XMLRPC_DEBUG_REFCOUNT
		printf ("calloc'd 0x%x\n", v);
#endif
      v->type = xmlrpc_empty;
      simplestring_init(&v->id);
      simplestring_init(&v->str);
   }
   return v;
}