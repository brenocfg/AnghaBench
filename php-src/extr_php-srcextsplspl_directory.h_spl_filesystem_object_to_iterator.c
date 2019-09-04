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
typedef  int /*<<< orphan*/  spl_filesystem_object ;
struct TYPE_4__ {int /*<<< orphan*/  intern; void* object; } ;
typedef  TYPE_1__ spl_filesystem_iterator ;

/* Variables and functions */
 TYPE_1__* ecalloc (int,int) ; 
 int /*<<< orphan*/  zend_iterator_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline spl_filesystem_iterator* spl_filesystem_object_to_iterator(spl_filesystem_object *obj)
{
	spl_filesystem_iterator    *it;

	it = ecalloc(1, sizeof(spl_filesystem_iterator));
	it->object = (void *)obj;
	zend_iterator_init(&it->intern);
	return it;
}