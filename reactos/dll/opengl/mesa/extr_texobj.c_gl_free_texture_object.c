#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct gl_texture_object {scalar_t__* Image; scalar_t__ Name; struct gl_texture_object* Next; } ;
struct gl_shared_state {int /*<<< orphan*/  TexObjects; struct gl_texture_object* TexObjectList; } ;
typedef  size_t GLuint ;

/* Variables and functions */
 int /*<<< orphan*/  HashRemove (int /*<<< orphan*/ ,scalar_t__) ; 
 size_t MAX_TEXTURE_LEVELS ; 
 int /*<<< orphan*/  assert (struct gl_texture_object*) ; 
 int /*<<< orphan*/  free (struct gl_texture_object*) ; 
 int /*<<< orphan*/  gl_free_texture_image (scalar_t__) ; 

void gl_free_texture_object( struct gl_shared_state *shared,
                             struct gl_texture_object *t )
{
   struct gl_texture_object *tprev, *tcurr;

   assert(t);

   /* unlink t from the linked list */
   if (shared) {
      tprev = NULL;
      tcurr = shared->TexObjectList;
      while (tcurr) {
         if (tcurr==t) {
            if (tprev) {
               tprev->Next = t->Next;
            }
            else {
               shared->TexObjectList = t->Next;
            }
            break;
         }
         tprev = tcurr;
         tcurr = tcurr->Next;
      }
   }

   if (t->Name) {
      /* remove from hash table */
      HashRemove(shared->TexObjects, t->Name);
   }

   /* free texture image */
   {
      GLuint i;
      for (i=0;i<MAX_TEXTURE_LEVELS;i++) {
         if (t->Image[i]) {
            gl_free_texture_image( t->Image[i] );
         }
      }
   }
   /* free this object */
   free( t );
}