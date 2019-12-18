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
struct darray {scalar_t__ num; scalar_t__ capacity; int /*<<< orphan*/ * array; } ;

/* Variables and functions */
 int /*<<< orphan*/  darray_free (struct darray*) ; 
 int /*<<< orphan*/  memcpy (struct darray*,struct darray*,int) ; 

__attribute__((used)) static inline void darray_move(struct darray *dst, struct darray *src)
{
	darray_free(dst);
	memcpy(dst, src, sizeof(struct darray));
	src->array = NULL;
	src->capacity = 0;
	src->num = 0;
}