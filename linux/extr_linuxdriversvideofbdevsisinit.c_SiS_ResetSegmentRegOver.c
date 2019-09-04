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
struct SiS_Private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SiS_SetSegmentRegOver (struct SiS_Private*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
SiS_ResetSegmentRegOver(struct SiS_Private *SiS_Pr)
{
   SiS_SetSegmentRegOver(SiS_Pr, 0);
}