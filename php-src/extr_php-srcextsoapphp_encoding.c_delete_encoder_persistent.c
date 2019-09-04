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
typedef  int /*<<< orphan*/  zval ;
typedef  TYPE_2__* encodePtr ;
struct TYPE_5__ {int /*<<< orphan*/ * map; TYPE_2__* type_str; TYPE_2__* ns; } ;
struct TYPE_6__ {TYPE_1__ details; } ;

/* Variables and functions */
 TYPE_2__* Z_PTR_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 

void delete_encoder_persistent(zval *zv)
{
	encodePtr t = Z_PTR_P(zv);
	if (t->details.ns) {
		free(t->details.ns);
	}
	if (t->details.type_str) {
		free(t->details.type_str);
	}
	/* we should never have mapping in persistent encoder */
	assert(t->details.map == NULL);
	free(t);
}