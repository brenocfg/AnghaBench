#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* next; int /*<<< orphan*/  value; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ nvram_tuple_t ;
struct TYPE_7__ {TYPE_1__** nvram_hash; } ;
typedef  TYPE_2__ nvram_handle_t ;

/* Variables and functions */
 int NVRAM_ARRAYSIZE (TYPE_1__**) ; 
 scalar_t__ malloc (int) ; 

nvram_tuple_t * nvram_getall(nvram_handle_t *h)
{
	int i;
	nvram_tuple_t *t, *l, *x;

	l = NULL;

	for (i = 0; i < NVRAM_ARRAYSIZE(h->nvram_hash); i++) {
		for (t = h->nvram_hash[i]; t; t = t->next) {
			if( (x = (nvram_tuple_t *) malloc(sizeof(nvram_tuple_t))) != NULL )
			{
				x->name  = t->name;
				x->value = t->value;
				x->next  = l;
				l = x;
			}
			else
			{
				break;
			}
		}
	}

	return l;
}