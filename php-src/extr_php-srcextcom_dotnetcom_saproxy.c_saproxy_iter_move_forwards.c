#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ zend_object_iterator ;
struct TYPE_5__ {scalar_t__ key; scalar_t__ imax; } ;
typedef  TYPE_2__ php_com_saproxy_iter ;

/* Variables and functions */
 scalar_t__ Z_PTR (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void saproxy_iter_move_forwards(zend_object_iterator *iter)
{
	php_com_saproxy_iter *I = (php_com_saproxy_iter*)Z_PTR(iter->data);

	if (++I->key >= I->imax) {
		I->key = -1;
	}
}