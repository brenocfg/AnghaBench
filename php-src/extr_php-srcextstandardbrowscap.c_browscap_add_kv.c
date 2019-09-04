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
typedef  int /*<<< orphan*/  zend_string ;
typedef  int /*<<< orphan*/  zend_bool ;
struct TYPE_5__ {int kv_used; int kv_size; TYPE_2__* kv; } ;
typedef  TYPE_1__ browser_data ;
typedef  int /*<<< orphan*/  browscap_kv ;
struct TYPE_6__ {int /*<<< orphan*/ * value; int /*<<< orphan*/ * key; } ;

/* Variables and functions */
 TYPE_2__* safe_perealloc (TYPE_2__*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void browscap_add_kv(
		browser_data *bdata, zend_string *key, zend_string *value, zend_bool persistent) {
	if (bdata->kv_used == bdata->kv_size) {
		bdata->kv_size *= 2;
		bdata->kv = safe_perealloc(bdata->kv, sizeof(browscap_kv), bdata->kv_size, 0, persistent);
	}

	bdata->kv[bdata->kv_used].key = key;
	bdata->kv[bdata->kv_used].value = value;
	bdata->kv_used++;
}