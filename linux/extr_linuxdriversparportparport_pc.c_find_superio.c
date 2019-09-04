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
struct superio_struct {scalar_t__ io; } ;
struct parport {scalar_t__ base; } ;

/* Variables and functions */
 int NR_SUPERIOS ; 
 struct superio_struct* superios ; 

__attribute__((used)) static struct superio_struct *find_superio(struct parport *p)
{
	int i;
	for (i = 0; i < NR_SUPERIOS; i++)
		if (superios[i].io == p->base)
			return &superios[i];
	return NULL;
}