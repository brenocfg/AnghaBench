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
typedef  scalar_t__ Linetype ;

/* Variables and functions */
 int /*<<< orphan*/  LT_FALSE ; 
 scalar_t__ LT_IF ; 
 int /*<<< orphan*/  LT_TRUE ; 

__attribute__((used)) static Linetype op_strict(int *p, int v, Linetype at, Linetype bt) {
	if(at == LT_IF || bt == LT_IF) return (LT_IF);
	return (*p = v, v ? LT_TRUE : LT_FALSE);
}