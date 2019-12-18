#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * next; scalar_t__ idx; } ;
typedef  TYPE_1__ fcgi_hash_buckets ;
struct TYPE_6__ {TYPE_3__* data; TYPE_1__* buckets; int /*<<< orphan*/ * list; int /*<<< orphan*/  hash_table; } ;
typedef  TYPE_2__ fcgi_hash ;
struct TYPE_7__ {int /*<<< orphan*/ * next; scalar_t__ pos; scalar_t__ end; scalar_t__ data; } ;
typedef  TYPE_3__ fcgi_data_seg ;

/* Variables and functions */
 int FCGI_HASH_SEG_SIZE ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void fcgi_hash_init(fcgi_hash *h)
{
	memset(h->hash_table, 0, sizeof(h->hash_table));
	h->list = NULL;
	h->buckets = (fcgi_hash_buckets*)malloc(sizeof(fcgi_hash_buckets));
	h->buckets->idx = 0;
	h->buckets->next = NULL;
	h->data = (fcgi_data_seg*)malloc(sizeof(fcgi_data_seg) - 1 + FCGI_HASH_SEG_SIZE);
	h->data->pos = h->data->data;
	h->data->end = h->data->pos + FCGI_HASH_SEG_SIZE;
	h->data->next = NULL;
}