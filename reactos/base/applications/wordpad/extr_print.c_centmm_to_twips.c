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
typedef  int /*<<< orphan*/  LONG ;

/* Variables and functions */
 int /*<<< orphan*/  CENTMM_PER_INCH ; 
 int /*<<< orphan*/  MulDiv (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TWIPS_PER_INCH ; 

__attribute__((used)) static LONG centmm_to_twips(int mm)
{
    return MulDiv(mm, TWIPS_PER_INCH, CENTMM_PER_INCH);
}