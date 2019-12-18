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
struct gl_attrib_node {int /*<<< orphan*/  kind; } ;
typedef  int /*<<< orphan*/  GLbitfield ;

/* Variables and functions */
 scalar_t__ malloc (int) ; 

__attribute__((used)) static struct gl_attrib_node *new_attrib_node( GLbitfield kind )
{
   struct gl_attrib_node *an;

   an = (struct gl_attrib_node *) malloc( sizeof(struct gl_attrib_node) );
   if (an) {
      an->kind = kind;
   }
   return an;
}