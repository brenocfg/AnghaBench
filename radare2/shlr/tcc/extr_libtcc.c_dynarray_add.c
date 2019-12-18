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

/* Variables and functions */
 void** realloc (void**,int) ; 

void dynarray_add(void ***ptab, int *nb_ptr, void *data)
{
	int nb, nb_alloc;
	void **pp;

	nb = *nb_ptr;
	pp = *ptab;
	/* every power of two we double array size */
	if ((nb & (nb - 1)) == 0) {
		if (!nb) {
			nb_alloc = 1;
		} else {
			nb_alloc = nb * 2;
		}
		pp = realloc (pp, nb_alloc * sizeof(void *));
		*ptab = pp;
	}
	pp[nb++] = data;
	*nb_ptr = nb;
}