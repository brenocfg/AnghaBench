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
typedef  int /*<<< orphan*/  float8 ;
typedef  int /*<<< orphan*/  BOX ;

/* Variables and functions */
 int /*<<< orphan*/  box_ht (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  box_wd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  float8_mul (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static float8
box_ar(BOX *box)
{
	return float8_mul(box_wd(box), box_ht(box));
}