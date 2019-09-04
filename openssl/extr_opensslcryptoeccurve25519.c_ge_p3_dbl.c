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
typedef  int /*<<< orphan*/  ge_p3 ;
typedef  int /*<<< orphan*/  ge_p2 ;
typedef  int /*<<< orphan*/  ge_p1p1 ;

/* Variables and functions */
 int /*<<< orphan*/  ge_p2_dbl (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ge_p3_to_p2 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void ge_p3_dbl(ge_p1p1 *r, const ge_p3 *p)
{
    ge_p2 q;
    ge_p3_to_p2(&q, p);
    ge_p2_dbl(r, &q);
}