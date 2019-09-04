#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned int len; void* data; } ;
typedef  TYPE_1__ DsoJsonStr ;

/* Variables and functions */
 void* calloc (int,int) ; 
 int /*<<< orphan*/  free (void*) ; 

__attribute__((used)) static void allocDsoStr (DsoJsonStr *dsoStr, unsigned int sz) {
	free (dsoStr->data);
	if (sz > 0) dsoStr->data = calloc (sz, 1);
	else dsoStr->data = calloc (10, 1);
	dsoStr->len = sz;
}