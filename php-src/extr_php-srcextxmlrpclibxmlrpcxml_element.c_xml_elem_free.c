#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  children; } ;
typedef  TYPE_1__ xml_element ;

/* Variables and functions */
 TYPE_1__* Q_Head (int /*<<< orphan*/ *) ; 
 TYPE_1__* Q_Next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xml_elem_free_non_recurse (TYPE_1__*) ; 

void xml_elem_free(xml_element* root) {
   if(root) {
      xml_element* kids = Q_Head(&root->children);
      while(kids) {
         xml_elem_free(kids);
         kids = Q_Next(&root->children);
      }
      xml_elem_free_non_recurse(root);
   }
}