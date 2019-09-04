#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_object_iterator ;
struct TYPE_2__ {int /*<<< orphan*/  i; } ;
typedef  TYPE_1__ ResourceBundle_iterator ;

/* Variables and functions */
 int /*<<< orphan*/  resourcebundle_iterator_invalidate (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void resourcebundle_iterator_step( zend_object_iterator *iter )
{
	ResourceBundle_iterator *iterator = (ResourceBundle_iterator *) iter;

	iterator->i++;
	resourcebundle_iterator_invalidate( iter );
}