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
struct TYPE_6__ {int /*<<< orphan*/  data; int /*<<< orphan*/  pos; struct TYPE_6__* next; scalar_t__ idx; } ;
typedef  TYPE_1__ fcgi_hash_buckets ;
struct TYPE_7__ {TYPE_1__* data; TYPE_1__* buckets; int /*<<< orphan*/ * list; int /*<<< orphan*/  hash_table; } ;
typedef  TYPE_2__ fcgi_hash ;
typedef  TYPE_1__ fcgi_data_seg ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void fcgi_hash_clean(fcgi_hash *h)
{
	memset(h->hash_table, 0, sizeof(h->hash_table));
	h->list = NULL;
	/* delete all bucket blocks except the first one */
	while (h->buckets->next) {
		fcgi_hash_buckets *q = h->buckets;

		h->buckets = h->buckets->next;
		free(q);
	}
	h->buckets->idx = 0;
	/* delete all data segments except the first one */
	while (h->data->next) {
		fcgi_data_seg *q = h->data;

		h->data = h->data->next;
		free(q);
	}
	h->data->pos = h->data->data;
}