#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {TYPE_2__* current; } ;
typedef  TYPE_1__ xml_elem_data ;
struct TYPE_4__ {struct TYPE_4__* parent; int /*<<< orphan*/  children; } ;

/* Variables and functions */
 int /*<<< orphan*/  Q_PushTail (int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static void _xmlrpc_endElement(void *userData, const char *name)
{
   xml_elem_data* mydata = (xml_elem_data*)userData;

   if(mydata && mydata->current && mydata->current->parent) {
      Q_PushTail(&mydata->current->parent->children, mydata->current);

      mydata->current = mydata->current->parent;
   }
}