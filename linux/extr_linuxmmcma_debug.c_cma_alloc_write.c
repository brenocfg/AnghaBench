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
typedef  int u64 ;
struct cma {int dummy; } ;

/* Variables and functions */
 int cma_alloc_mem (struct cma*,int) ; 

__attribute__((used)) static int cma_alloc_write(void *data, u64 val)
{
	int pages = val;
	struct cma *cma = data;

	return cma_alloc_mem(cma, pages);
}