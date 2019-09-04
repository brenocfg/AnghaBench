#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* XMLRPC_VALUE ;
struct TYPE_9__ {scalar_t__ iRefCount; int type; int /*<<< orphan*/  str; int /*<<< orphan*/  id; struct TYPE_9__* v; struct TYPE_9__* q; } ;
typedef  int /*<<< orphan*/  STRUCT_XMLRPC_VALUE ;

/* Variables and functions */
 int /*<<< orphan*/  Q_Destroy (TYPE_1__*) ; 
 int /*<<< orphan*/  Q_Head (TYPE_1__*) ; 
 TYPE_1__* Q_Next (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  my_free (TYPE_1__*) ; 
 int /*<<< orphan*/  simplestring_free (int /*<<< orphan*/ *) ; 
#define  xmlrpc_base64 135 
#define  xmlrpc_boolean 134 
#define  xmlrpc_datetime 133 
#define  xmlrpc_double 132 
#define  xmlrpc_empty 131 
#define  xmlrpc_int 130 
#define  xmlrpc_string 129 
#define  xmlrpc_vector 128 

void XMLRPC_CleanupValue(XMLRPC_VALUE value) {
   if(value) {
      if(value->iRefCount > 0) {
         value->iRefCount --;
      }

#ifdef XMLRPC_DEBUG_REFCOUNT
      if(value->id.str) {
			printf ("decremented refcount of %s, now %i\n", value->id.str,
					  value->iRefCount);
      }
      else {
			printf ("decremented refcount of 0x%x, now %i\n", value,
					  value->iRefCount);
      }
#endif

      if(value->type == xmlrpc_vector) {
         if(value->v) {
            if(value->iRefCount == 0) {
               XMLRPC_VALUE cur = (XMLRPC_VALUE)Q_Head(value->v->q);
               while( cur ) {
                  XMLRPC_CleanupValue(cur);

                  /* Make sure some idiot didn't include a vector as a child of itself
                   * and thus it would have already free'd these.
                   */
                  if(value->v && value->v->q) {
                     cur = Q_Next(value->v->q);
                  }
                  else {
                     break;
                  }
               }

               Q_Destroy(value->v->q);
               my_free(value->v->q);
               my_free(value->v);
            }
         }
      }


      if(value->iRefCount == 0) {

         /* guard against freeing invalid types */
         switch(value->type) {
            case xmlrpc_empty:
            case xmlrpc_base64:
            case xmlrpc_boolean:
            case xmlrpc_datetime:
            case xmlrpc_double:
            case xmlrpc_int:
            case xmlrpc_string:
            case xmlrpc_vector:
#ifdef XMLRPC_DEBUG_REFCOUNT
               if(value->id.str) {
                  printf("free'd %s\n", value->id.str);
               }
               else {
                  printf("free'd 0x%x\n", value);
               }
#endif
               simplestring_free(&value->id);
               simplestring_free(&value->str);

               memset(value, 0, sizeof(STRUCT_XMLRPC_VALUE));
               my_free(value);
               break;
            default:
				/* fprintf (stderr,
							"xmlrpc: attempted to free value of invalid type\n"); */
               break;
         }
      }
   }
}