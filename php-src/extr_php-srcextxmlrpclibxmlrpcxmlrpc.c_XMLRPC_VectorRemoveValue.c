#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ q_iter ;
typedef  TYPE_2__* XMLRPC_VALUE ;
struct TYPE_8__ {TYPE_1__* v; } ;
struct TYPE_7__ {scalar_t__ q; } ;

/* Variables and functions */
 int /*<<< orphan*/  Q_Iter_Del (scalar_t__,scalar_t__) ; 
 TYPE_2__* Q_Iter_Get_F (scalar_t__) ; 
 scalar_t__ Q_Iter_Head_F (scalar_t__) ; 
 scalar_t__ Q_Iter_Next_F (scalar_t__) ; 
 int /*<<< orphan*/  XMLRPC_CleanupValue (TYPE_2__*) ; 

int XMLRPC_VectorRemoveValue(XMLRPC_VALUE vector, XMLRPC_VALUE value) {
   if(vector && vector->v && vector->v->q && value) {
       q_iter qi = Q_Iter_Head_F(vector->v->q);

       while(qi) {
          XMLRPC_VALUE xIter = Q_Iter_Get_F(qi);
          if(xIter == value) {
             XMLRPC_CleanupValue(xIter);
             Q_Iter_Del(vector->v->q, qi);
             return 1;
          }
          qi = Q_Iter_Next_F(qi);
       }
   }
   return 0;
}