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
typedef  int ut32 ;

/* Variables and functions */
 int UT32_MAX ; 

__attribute__((used)) static ut32 mask32(ut32 mb, ut32 me) {
	ut32 maskmb = UT32_MAX >> mb;
	ut32 maskme = UT32_MAX << (31 - me);
	return (mb <= me) ? maskmb & maskme : maskmb | maskme;
}