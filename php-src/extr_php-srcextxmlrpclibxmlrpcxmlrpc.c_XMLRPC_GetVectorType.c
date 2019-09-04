#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  XMLRPC_VECTOR_TYPE ;
typedef  TYPE_2__* XMLRPC_VALUE ;
struct TYPE_5__ {TYPE_1__* v; } ;
struct TYPE_4__ {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  xmlrpc_none ; 

XMLRPC_VECTOR_TYPE XMLRPC_GetVectorType(XMLRPC_VALUE value) {
   return(value && value->v) ? value->v->type : xmlrpc_none;
}