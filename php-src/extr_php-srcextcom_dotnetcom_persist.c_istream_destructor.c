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
typedef  int /*<<< orphan*/  zend_resource ;
struct TYPE_6__ {scalar_t__ refcount; TYPE_1__* stream; int /*<<< orphan*/ * res; } ;
typedef  TYPE_2__ php_istream ;
struct TYPE_5__ {int /*<<< orphan*/ * res; } ;
typedef  int /*<<< orphan*/  IUnknown ;

/* Variables and functions */
 int /*<<< orphan*/  CoDisconnectObject (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CoTaskMemFree (TYPE_2__*) ; 
 int /*<<< orphan*/  zend_list_delete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void istream_destructor(php_istream *stm)
{
	if (stm->res) {
		zend_resource *res = stm->res;
		stm->res = NULL;
		zend_list_delete(res);
		return;
	}

	if (stm->refcount > 0) {
		CoDisconnectObject((IUnknown*)stm, 0);
	}

	zend_list_delete(stm->stream->res);

	CoTaskMemFree(stm);
}