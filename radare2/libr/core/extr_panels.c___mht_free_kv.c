#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ value; int /*<<< orphan*/  key; } ;
typedef  int /*<<< orphan*/  RPanelsMenuItem ;
typedef  TYPE_1__ HtPPKv ;

/* Variables and functions */
 int /*<<< orphan*/  __free_menu_item (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 

void __mht_free_kv(HtPPKv *kv) {
	free (kv->key);
	__free_menu_item ((RPanelsMenuItem *)kv->value);
}