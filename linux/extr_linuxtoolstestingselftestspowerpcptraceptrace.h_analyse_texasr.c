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

/* Variables and functions */
 unsigned long TEXASR_ABT ; 
 unsigned long TEXASR_DA ; 
 unsigned long TEXASR_FO ; 
 unsigned long TEXASR_FP ; 
 unsigned long TEXASR_FS ; 
 unsigned long TEXASR_HV ; 
 unsigned long TEXASR_IC ; 
 unsigned long TEXASR_IFC ; 
 unsigned long TEXASR_NO ; 
 unsigned long TEXASR_NTC ; 
 unsigned long TEXASR_PR ; 
 unsigned long TEXASR_ROT ; 
 unsigned long TEXASR_SIC ; 
 unsigned long TEXASR_SPD ; 
 unsigned long TEXASR_TC ; 
 unsigned long TEXASR_TE ; 
 unsigned long TEXASR_TIC ; 
 unsigned long get_tfiar () ; 
 int /*<<< orphan*/  printf (char*,...) ; 

void analyse_texasr(unsigned long texasr)
{
	printf("TEXASR: %16lx\t", texasr);

	if (texasr & TEXASR_FP)
		printf("TEXASR_FP  ");

	if (texasr & TEXASR_DA)
		printf("TEXASR_DA  ");

	if (texasr & TEXASR_NO)
		printf("TEXASR_NO  ");

	if (texasr & TEXASR_FO)
		printf("TEXASR_FO  ");

	if (texasr & TEXASR_SIC)
		printf("TEXASR_SIC  ");

	if (texasr & TEXASR_NTC)
		printf("TEXASR_NTC  ");

	if (texasr & TEXASR_TC)
		printf("TEXASR_TC  ");

	if (texasr & TEXASR_TIC)
		printf("TEXASR_TIC  ");

	if (texasr & TEXASR_IC)
		printf("TEXASR_IC  ");

	if (texasr & TEXASR_IFC)
		printf("TEXASR_IFC  ");

	if (texasr & TEXASR_ABT)
		printf("TEXASR_ABT  ");

	if (texasr & TEXASR_SPD)
		printf("TEXASR_SPD  ");

	if (texasr & TEXASR_HV)
		printf("TEXASR_HV  ");

	if (texasr & TEXASR_PR)
		printf("TEXASR_PR  ");

	if (texasr & TEXASR_FS)
		printf("TEXASR_FS  ");

	if (texasr & TEXASR_TE)
		printf("TEXASR_TE  ");

	if (texasr & TEXASR_ROT)
		printf("TEXASR_ROT  ");

	printf("TFIAR :%lx\n", get_tfiar());
}