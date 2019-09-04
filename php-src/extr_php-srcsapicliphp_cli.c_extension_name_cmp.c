#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ data; } ;
typedef  TYPE_1__ zend_llist_element ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ zend_extension ;

/* Variables and functions */
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int extension_name_cmp(const zend_llist_element **f, const zend_llist_element **s) /* {{{ */
{
	zend_extension *fe = (zend_extension*)(*f)->data;
	zend_extension *se = (zend_extension*)(*s)->data;
	return strcmp(fe->name, se->name);
}