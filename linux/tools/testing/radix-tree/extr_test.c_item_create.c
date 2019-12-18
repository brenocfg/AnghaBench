#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct item {unsigned long index; unsigned int order; } ;

/* Variables and functions */
 struct item* malloc (int) ; 

struct item *item_create(unsigned long index, unsigned int order)
{
	struct item *ret = malloc(sizeof(*ret));

	ret->index = index;
	ret->order = order;
	return ret;
}