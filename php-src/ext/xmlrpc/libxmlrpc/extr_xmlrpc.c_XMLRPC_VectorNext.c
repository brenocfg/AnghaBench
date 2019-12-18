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
typedef  TYPE_2__* XMLRPC_VALUE ;
struct TYPE_6__ {scalar_t__ type; TYPE_1__* v; } ;
struct TYPE_5__ {int /*<<< orphan*/  q; } ;

/* Variables and functions */
 scalar_t__ Q_Next (int /*<<< orphan*/ ) ; 
 scalar_t__ xmlrpc_vector ; 

XMLRPC_VALUE XMLRPC_VectorNext(XMLRPC_VALUE value) {
   XMLRPC_VALUE xReturn = NULL;
   if(value && value->type == xmlrpc_vector && value->v) {
      xReturn = (XMLRPC_VALUE)Q_Next(value->v->q);
   }
   return xReturn;
}