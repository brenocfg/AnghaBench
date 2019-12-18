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
typedef  int /*<<< orphan*/  gf ;

/* Variables and functions */
 int /*<<< orphan*/  gf_bias (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gf_sub_RAW (int /*<<< orphan*/ ,int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  gf_weak_reduce (int /*<<< orphan*/ ) ; 

void gf_sub(gf d, const gf a, const gf b)
{
    gf_sub_RAW(d, a, b);
    gf_bias(d, 2);
    gf_weak_reduce(d);
}