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
struct snd_akm4xxx {int dummy; } ;

/* Variables and functions */
 unsigned char AK4620_CKS0 ; 
 unsigned char AK4620_CKS1 ; 
 unsigned char AK4620_DFS0 ; 
 unsigned char AK4620_DFS1 ; 
 int /*<<< orphan*/  AK4620_DFS_REG ; 
 int /*<<< orphan*/  qtet_akm_set_regs (struct snd_akm4xxx*,int /*<<< orphan*/ ,unsigned char,unsigned char) ; 

__attribute__((used)) static void qtet_akm_set_rate_val(struct snd_akm4xxx *ak, unsigned int rate)
{
	unsigned char ak4620_dfs;

	if (rate == 0)  /* no hint - S/PDIF input is master or the new spdif
			   input rate undetected, simply return */
		return;

	/* adjust DFS on codecs - see datasheet */
	if (rate > 108000)
		ak4620_dfs = AK4620_DFS1 | AK4620_CKS1;
	else if (rate > 54000)
		ak4620_dfs = AK4620_DFS0 | AK4620_CKS0;
	else
		ak4620_dfs = 0;

	/* set new value */
	qtet_akm_set_regs(ak, AK4620_DFS_REG, AK4620_DFS0 | AK4620_DFS1 |
			AK4620_CKS0 | AK4620_CKS1, ak4620_dfs);
}