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
typedef  int /*<<< orphan*/  smallfelem ;
typedef  int /*<<< orphan*/  longfelem ;
typedef  int /*<<< orphan*/  felem ;

/* Variables and functions */
 int /*<<< orphan*/  felem_contract (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  felem_reduce (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smallfelem_square (int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 

__attribute__((used)) static void smallfelem_square_contract(smallfelem out, const smallfelem in)
{
    longfelem longtmp;
    felem tmp;

    smallfelem_square(longtmp, in);
    felem_reduce(tmp, longtmp);
    felem_contract(out, tmp);
}