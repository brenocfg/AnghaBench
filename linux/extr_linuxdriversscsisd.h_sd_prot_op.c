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
 unsigned int const SCSI_PROT_NORMAL ; 
 unsigned int const SCSI_PROT_READ_INSERT ; 
 unsigned int const SCSI_PROT_READ_PASS ; 
 unsigned int const SCSI_PROT_READ_STRIP ; 
 unsigned int const SCSI_PROT_WRITE_INSERT ; 
 unsigned int const SCSI_PROT_WRITE_PASS ; 
 unsigned int const SCSI_PROT_WRITE_STRIP ; 

__attribute__((used)) static inline unsigned int sd_prot_op(bool write, bool dix, bool dif)
{
	/* Lookup table: bit 2 (write), bit 1 (dix), bit 0 (dif) */
	const unsigned int ops[] = {	/* wrt dix dif */
		SCSI_PROT_NORMAL,	/*  0	0   0  */
		SCSI_PROT_READ_STRIP,	/*  0	0   1  */
		SCSI_PROT_READ_INSERT,	/*  0	1   0  */
		SCSI_PROT_READ_PASS,	/*  0	1   1  */
		SCSI_PROT_NORMAL,	/*  1	0   0  */
		SCSI_PROT_WRITE_INSERT, /*  1	0   1  */
		SCSI_PROT_WRITE_STRIP,	/*  1	1   0  */
		SCSI_PROT_WRITE_PASS,	/*  1	1   1  */
	};

	return ops[write << 2 | dix << 1 | dif];
}