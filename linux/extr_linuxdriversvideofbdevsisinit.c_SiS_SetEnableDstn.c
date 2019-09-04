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
struct SiS_Private {int SiS_IF_DEF_DSTN; } ;

/* Variables and functions */

void
SiS_SetEnableDstn(struct SiS_Private *SiS_Pr, int enable)
{
   SiS_Pr->SiS_IF_DEF_DSTN = enable ? 1 : 0;
}