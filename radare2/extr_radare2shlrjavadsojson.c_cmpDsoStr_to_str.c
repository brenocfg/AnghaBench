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
struct TYPE_3__ {scalar_t__ data; } ;
typedef  TYPE_1__ DsoJsonStr ;

/* Variables and functions */
 int strcmp (scalar_t__,char*) ; 

__attribute__((used)) static int cmpDsoStr_to_str (DsoJsonStr *dsoStr1, char *dsoStr2) {
	if (dsoStr1 && dsoStr1->data && dsoStr2)
		return strcmp (dsoStr1->data, dsoStr2);
	return -1;
}