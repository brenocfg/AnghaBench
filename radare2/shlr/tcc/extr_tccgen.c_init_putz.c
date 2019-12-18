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
typedef  int /*<<< orphan*/  CType ;

/* Variables and functions */
 int /*<<< orphan*/  VT_LOCAL ; 
 int /*<<< orphan*/  vpushi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vpushs (int) ; 
 int /*<<< orphan*/  vseti (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void init_putz(CType *t, unsigned long c, int size) {
	vseti (VT_LOCAL, c);
	vpushi (0);
	vpushs (size);
}