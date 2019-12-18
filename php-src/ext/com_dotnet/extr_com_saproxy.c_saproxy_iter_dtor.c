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
struct TYPE_5__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ zend_object_iterator ;
struct TYPE_6__ {struct TYPE_6__* indices; int /*<<< orphan*/  proxy_obj; } ;
typedef  TYPE_2__ php_com_saproxy_iter ;

/* Variables and functions */
 scalar_t__ Z_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efree (TYPE_2__*) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void saproxy_iter_dtor(zend_object_iterator *iter)
{
	php_com_saproxy_iter *I = (php_com_saproxy_iter*)Z_PTR(iter->data);

	zval_ptr_dtor(&I->proxy_obj);

	efree(I->indices);
	efree(I);
}