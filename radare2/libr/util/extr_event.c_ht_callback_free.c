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
struct TYPE_3__ {scalar_t__ value; } ;
typedef  int /*<<< orphan*/  RVector ;
typedef  TYPE_1__ HtUPKv ;

/* Variables and functions */
 int /*<<< orphan*/  r_vector_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ht_callback_free(HtUPKv *kv) {
	r_vector_free ((RVector *)kv->value);
}