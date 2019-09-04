#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  q_iter ;
typedef  TYPE_4__* XMLRPC_VALUE ;
struct TYPE_18__ {int /*<<< orphan*/  len; int /*<<< orphan*/  str; } ;
struct TYPE_17__ {int /*<<< orphan*/  len; int /*<<< orphan*/  str; } ;
struct TYPE_20__ {int type; TYPE_3__* v; int /*<<< orphan*/  d; int /*<<< orphan*/  i; TYPE_2__ str; TYPE_1__ id; } ;
struct TYPE_19__ {int /*<<< orphan*/  type; int /*<<< orphan*/  q; } ;

/* Variables and functions */
 TYPE_4__* Q_Iter_Get_F (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Q_Iter_Head_F (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Q_Iter_Next_F (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XMLRPC_AddValueToVector (TYPE_4__*,TYPE_4__*) ; 
 TYPE_4__* XMLRPC_CreateValueEmpty () ; 
 int /*<<< orphan*/  XMLRPC_SetIsVector (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XMLRPC_SetValueDateTime (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XMLRPC_SetValueDouble (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XMLRPC_SetValueID (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XMLRPC_SetValueInt (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XMLRPC_SetValueString (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  xmlrpc_base64 134 
#define  xmlrpc_boolean 133 
#define  xmlrpc_datetime 132 
#define  xmlrpc_double 131 
#define  xmlrpc_int 130 
#define  xmlrpc_string 129 
#define  xmlrpc_vector 128 

XMLRPC_VALUE XMLRPC_DupValueNew (XMLRPC_VALUE xSource) {
	XMLRPC_VALUE xReturn = NULL;
	if (xSource) {
		xReturn = XMLRPC_CreateValueEmpty ();
		if (xSource->id.len) {
			XMLRPC_SetValueID (xReturn, xSource->id.str, xSource->id.len);
		}

		switch (xSource->type) {
		case xmlrpc_int:
		case xmlrpc_boolean:
			XMLRPC_SetValueInt (xReturn, xSource->i);
			break;
		case xmlrpc_string:
		case xmlrpc_base64:
			XMLRPC_SetValueString (xReturn, xSource->str.str, xSource->str.len);
			break;
		case xmlrpc_datetime:
			XMLRPC_SetValueDateTime (xReturn, xSource->i);
			break;
		case xmlrpc_double:
			XMLRPC_SetValueDouble (xReturn, xSource->d);
			break;
		case xmlrpc_vector:
			{
				q_iter qi = Q_Iter_Head_F (xSource->v->q);
				XMLRPC_SetIsVector (xReturn, xSource->v->type);

				while (qi) {
					XMLRPC_VALUE xIter = Q_Iter_Get_F (qi);
					XMLRPC_AddValueToVector (xReturn, XMLRPC_DupValueNew (xIter));
					qi = Q_Iter_Next_F (qi);
				}
			}
			break;
		default:
			break;
		}
	}
	return xReturn;
}