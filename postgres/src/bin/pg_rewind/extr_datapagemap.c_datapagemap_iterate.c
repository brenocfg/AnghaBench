#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  datapagemap_t ;
struct TYPE_4__ {scalar_t__ nextblkno; int /*<<< orphan*/ * map; } ;
typedef  TYPE_1__ datapagemap_iterator_t ;

/* Variables and functions */
 TYPE_1__* pg_malloc (int) ; 

datapagemap_iterator_t *
datapagemap_iterate(datapagemap_t *map)
{
	datapagemap_iterator_t *iter;

	iter = pg_malloc(sizeof(datapagemap_iterator_t));
	iter->map = map;
	iter->nextblkno = 0;

	return iter;
}