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
struct TYPE_4__ {int /*<<< orphan*/  iRefCount; } ;

/* Variables and functions */

XMLRPC_VALUE XMLRPC_CopyValue(XMLRPC_VALUE value) {
   if(value) {
      value->iRefCount ++;
#ifdef XMLRPC_DEBUG_REFCOUNT
      if(value->id.str) {
			printf ("incremented refcount of %s, now %i\n", value->id.str,
					  value->iRefCount);
		}
		else {
			printf ("incremented refcount of 0x%x, now %i\n", value,
					  value->iRefCount);
      }
#endif
   }
   return value;
}