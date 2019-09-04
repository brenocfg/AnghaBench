#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  text; int /*<<< orphan*/ * name; int /*<<< orphan*/  attrs; int /*<<< orphan*/  children; struct TYPE_7__* val; struct TYPE_7__* key; } ;
typedef  TYPE_1__ xml_element_attr ;
typedef  TYPE_1__ xml_element ;

/* Variables and functions */
 int /*<<< orphan*/  Q_Destroy (int /*<<< orphan*/ *) ; 
 TYPE_1__* Q_Head (int /*<<< orphan*/ *) ; 
 TYPE_1__* Q_Next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efree (char*) ; 
 int /*<<< orphan*/  my_free (TYPE_1__*) ; 
 int /*<<< orphan*/  simplestring_free (int /*<<< orphan*/ *) ; 

void xml_elem_free_non_recurse(xml_element* root) {
   if(root) {
      xml_element_attr* attrs = Q_Head(&root->attrs);
      while(attrs) {
         my_free(attrs->key);
         my_free(attrs->val);
         my_free(attrs);
         attrs = Q_Next(&root->attrs);
      }

      Q_Destroy(&root->children);
      Q_Destroy(&root->attrs);
      if(root->name) {
          efree((char *)root->name);
          root->name = NULL;
      }
      simplestring_free(&root->text);
      my_free(root);
   }
}