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
struct gl_shared_state {int /*<<< orphan*/  TexObjects; scalar_t__ TexObjectList; int /*<<< orphan*/  DisplayList; } ;
typedef  scalar_t__ GLuint ;
typedef  int /*<<< orphan*/  GLcontext ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteHashTable (int /*<<< orphan*/ ) ; 
 scalar_t__ HashFirstEntry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct gl_shared_state*) ; 
 int /*<<< orphan*/  gl_destroy_list (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  gl_free_texture_object (struct gl_shared_state*,scalar_t__) ; 

__attribute__((used)) static void free_shared_state( GLcontext *ctx, struct gl_shared_state *ss )
{
   /* Free display lists */
   while (1) {
      GLuint list = HashFirstEntry(ss->DisplayList);
      if (list) {
         gl_destroy_list(ctx, list);
      }
      else {
         break;
      }
   }
   DeleteHashTable(ss->DisplayList);

   /* Free texture objects */
   while (ss->TexObjectList)
   {
      /* this function removes from linked list too! */
      gl_free_texture_object(ss, ss->TexObjectList);
   }
   DeleteHashTable(ss->TexObjects);

   free(ss);
}