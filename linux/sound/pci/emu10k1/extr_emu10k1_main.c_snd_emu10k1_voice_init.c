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
struct snd_emu10k1 {scalar_t__ audigy; } ;

/* Variables and functions */
 int ATKHLDM ; 
 int ATKHLDV ; 
 int A_FXRT1 ; 
 int A_FXRT2 ; 
 int A_SENDAMOUNTS ; 
 int CCCA ; 
 int CCR ; 
 int CPF ; 
 int CVCF ; 
 int DCYSUSM ; 
 int DCYSUSV ; 
 int DSL ; 
 int ENVVAL ; 
 int ENVVOL ; 
 int FM2FRQ2 ; 
 int FMMOD ; 
 int FXRT ; 
 int IFATN ; 
 int IP ; 
 int LFOVAL1 ; 
 int LFOVAL2 ; 
 int PEFE ; 
 int PSST ; 
 int PTRX ; 
 int TEMPENV ; 
 int TREMFRQ ; 
 int VTFT ; 
 int Z1 ; 
 int Z2 ; 
 int /*<<< orphan*/  snd_emu10k1_ptr_write (struct snd_emu10k1*,int,int,int) ; 

void snd_emu10k1_voice_init(struct snd_emu10k1 *emu, int ch)
{
	snd_emu10k1_ptr_write(emu, DCYSUSV, ch, 0);
	snd_emu10k1_ptr_write(emu, IP, ch, 0);
	snd_emu10k1_ptr_write(emu, VTFT, ch, 0xffff);
	snd_emu10k1_ptr_write(emu, CVCF, ch, 0xffff);
	snd_emu10k1_ptr_write(emu, PTRX, ch, 0);
	snd_emu10k1_ptr_write(emu, CPF, ch, 0);
	snd_emu10k1_ptr_write(emu, CCR, ch, 0);

	snd_emu10k1_ptr_write(emu, PSST, ch, 0);
	snd_emu10k1_ptr_write(emu, DSL, ch, 0x10);
	snd_emu10k1_ptr_write(emu, CCCA, ch, 0);
	snd_emu10k1_ptr_write(emu, Z1, ch, 0);
	snd_emu10k1_ptr_write(emu, Z2, ch, 0);
	snd_emu10k1_ptr_write(emu, FXRT, ch, 0x32100000);

	snd_emu10k1_ptr_write(emu, ATKHLDM, ch, 0);
	snd_emu10k1_ptr_write(emu, DCYSUSM, ch, 0);
	snd_emu10k1_ptr_write(emu, IFATN, ch, 0xffff);
	snd_emu10k1_ptr_write(emu, PEFE, ch, 0);
	snd_emu10k1_ptr_write(emu, FMMOD, ch, 0);
	snd_emu10k1_ptr_write(emu, TREMFRQ, ch, 24);	/* 1 Hz */
	snd_emu10k1_ptr_write(emu, FM2FRQ2, ch, 24);	/* 1 Hz */
	snd_emu10k1_ptr_write(emu, TEMPENV, ch, 0);

	/*** these are last so OFF prevents writing ***/
	snd_emu10k1_ptr_write(emu, LFOVAL2, ch, 0);
	snd_emu10k1_ptr_write(emu, LFOVAL1, ch, 0);
	snd_emu10k1_ptr_write(emu, ATKHLDV, ch, 0);
	snd_emu10k1_ptr_write(emu, ENVVOL, ch, 0);
	snd_emu10k1_ptr_write(emu, ENVVAL, ch, 0);

	/* Audigy extra stuffs */
	if (emu->audigy) {
		snd_emu10k1_ptr_write(emu, 0x4c, ch, 0); /* ?? */
		snd_emu10k1_ptr_write(emu, 0x4d, ch, 0); /* ?? */
		snd_emu10k1_ptr_write(emu, 0x4e, ch, 0); /* ?? */
		snd_emu10k1_ptr_write(emu, 0x4f, ch, 0); /* ?? */
		snd_emu10k1_ptr_write(emu, A_FXRT1, ch, 0x03020100);
		snd_emu10k1_ptr_write(emu, A_FXRT2, ch, 0x3f3f3f3f);
		snd_emu10k1_ptr_write(emu, A_SENDAMOUNTS, ch, 0);
	}
}