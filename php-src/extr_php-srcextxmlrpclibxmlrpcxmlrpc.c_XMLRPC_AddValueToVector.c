#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* XMLRPC_VALUE ;
struct TYPE_9__ {int /*<<< orphan*/  len; } ;
struct TYPE_11__ {scalar_t__ type; TYPE_2__* v; TYPE_1__ id; } ;
struct TYPE_10__ {scalar_t__ type; scalar_t__ q; } ;

/* Variables and functions */
 int /*<<< orphan*/  Q_PushTail (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XMLRPC_CopyValue (TYPE_3__*) ; 
 int /*<<< orphan*/  isDuplicateEntry (TYPE_3__*,TYPE_3__*) ; 
#define  xmlrpc_base64 135 
#define  xmlrpc_boolean 134 
#define  xmlrpc_datetime 133 
#define  xmlrpc_double 132 
#define  xmlrpc_empty 131 
#define  xmlrpc_int 130 
#define  xmlrpc_string 129 
#define  xmlrpc_vector 128 
 scalar_t__ xmlrpc_vector_array ; 
 scalar_t__ xmlrpc_vector_none ; 

int XMLRPC_AddValueToVector(XMLRPC_VALUE target, XMLRPC_VALUE source) {
   if(target && source) {
      if(target->type == xmlrpc_vector && target->v &&
         target->v->q && target->v->type != xmlrpc_vector_none) {

         /* guard against putting value of unknown type into vector */
         switch(source->type) {
            case xmlrpc_empty:
            case xmlrpc_base64:
            case xmlrpc_boolean:
            case xmlrpc_datetime:
            case xmlrpc_double:
            case xmlrpc_int:
            case xmlrpc_string:
            case xmlrpc_vector:
               /* Guard against putting a key/val pair into an array vector */
               if( !(source->id.len && target->v->type == xmlrpc_vector_array) ) {
					if (isDuplicateEntry (target, source)
						 || Q_PushTail (target->v->q, XMLRPC_CopyValue (source))) {
                     return 1;
                  }
               }
               else {
					/* fprintf (stderr,
								"xmlrpc: attempted to add key/val pair to vector of type array\n"); */
               }
               break;
            default:
				/* fprintf (stderr,
							"xmlrpc: attempted to add value of unknown type to vector\n"); */
               break;
         }
      }
   }
   return 0;
}