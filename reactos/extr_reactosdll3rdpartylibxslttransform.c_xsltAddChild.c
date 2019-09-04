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
typedef  int /*<<< orphan*/ * xmlNodePtr ;

/* Variables and functions */
 int /*<<< orphan*/ * xmlAddChild (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlFreeNode (int /*<<< orphan*/ *) ; 

__attribute__((used)) static xmlNodePtr
xsltAddChild(xmlNodePtr parent, xmlNodePtr cur) {
   xmlNodePtr ret;

   if (cur == NULL)
       return(NULL);
   if (parent == NULL) {
       xmlFreeNode(cur);
       return(NULL);
   }
   ret = xmlAddChild(parent, cur);

   return(ret);
}