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
typedef  int /*<<< orphan*/  queue ;
typedef  void* XMLRPC_VECTOR_TYPE ;
typedef  TYPE_1__* XMLRPC_VALUE ;
struct TYPE_5__ {void* type; int /*<<< orphan*/ * q; } ;
struct TYPE_4__ {scalar_t__ type; TYPE_2__* v; } ;
typedef  int /*<<< orphan*/  STRUCT_XMLRPC_VECTOR ;

/* Variables and functions */
 int /*<<< orphan*/  Q_Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Q_Size (int /*<<< orphan*/ *) ; 
 TYPE_2__* ecalloc (int,int) ; 
 scalar_t__ emalloc (int) ; 
 scalar_t__ xmlrpc_vector ; 

int XMLRPC_SetIsVector(XMLRPC_VALUE value, XMLRPC_VECTOR_TYPE type) {
   int bSuccess = 0;

	if (value) {
		/* we can change the type so long as nothing is currently stored. */
		if(value->type == xmlrpc_vector) {
			if(value->v) {
				if(!Q_Size(value->v->q)) {
					value->v->type = type;
				}
			}
		}
		else {
      value->v = ecalloc(1, sizeof(STRUCT_XMLRPC_VECTOR));
      if(value->v) {
         value->v->q = (queue*)emalloc(sizeof(queue));
         if(value->v->q) {
            Q_Init(value->v->q);
            value->v->type = type;
            value->type = xmlrpc_vector;
            bSuccess = 1;
         }
      }
   }
	}

   return bSuccess;
}