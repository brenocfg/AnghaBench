#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ ptr; } ;
typedef  TYPE_1__ zend_resource ;
struct TYPE_7__ {size_t id; scalar_t__ pdict; TYPE_3__* pbroker; } ;
typedef  TYPE_2__ enchant_dict ;
struct TYPE_8__ {int /*<<< orphan*/  rsrc; int /*<<< orphan*/ ** dict; int /*<<< orphan*/  pbroker; } ;
typedef  TYPE_3__ enchant_broker ;

/* Variables and functions */
 int /*<<< orphan*/  efree (TYPE_2__*) ; 
 int /*<<< orphan*/  enchant_broker_free_dict (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  zend_list_delete (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void php_enchant_dict_free(zend_resource *rsrc) /* {{{ */

{
	if (rsrc->ptr) {
		enchant_dict *pdict = (enchant_dict *)rsrc->ptr;
		if (pdict) {
			enchant_broker *pbroker = pdict->pbroker;

			if (pdict->pdict && pbroker) {
				enchant_broker_free_dict(pbroker->pbroker, pdict->pdict);
			}

			pbroker->dict[pdict->id] = NULL;
			efree(pdict);
			zend_list_delete(pbroker->rsrc);
		}
	}
}