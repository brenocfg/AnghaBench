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
typedef  int /*<<< orphan*/  params ;

/* Variables and functions */

__attribute__((used)) static double box(params *p, double x)
{
    // This is mathematically 1.0 everywhere, the clipping is done implicitly
    // based on the radius.
    return 1.0;
}