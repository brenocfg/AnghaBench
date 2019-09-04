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
typedef  int timelib_sll ;

/* Variables and functions */
 int positive_mod (int,int) ; 

__attribute__((used)) static timelib_sll century_value(timelib_sll j)
{
	return 6 - positive_mod(j, 4) * 2;
}