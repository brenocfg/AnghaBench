#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  text; int /*<<< orphan*/  attrs; int /*<<< orphan*/  children; } ;
typedef  TYPE_1__ xml_element ;

/* Variables and functions */
 int /*<<< orphan*/  Q_Init (int /*<<< orphan*/ *) ; 
 TYPE_1__* ecalloc (int,int) ; 
 int /*<<< orphan*/  simplestring_addn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  simplestring_init (int /*<<< orphan*/ *) ; 

xml_element* xml_elem_new() {
   xml_element* elem = ecalloc(1, sizeof(xml_element));
   if(elem) {
      Q_Init(&elem->children);
      Q_Init(&elem->attrs);
      simplestring_init(&elem->text);

      /* init empty string in case we don't find any char data */
      simplestring_addn(&elem->text, "", 0);
   }
   return elem;
}