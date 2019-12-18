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
struct rme96 {int areg; int rcreg; scalar_t__ iobase; } ;

/* Variables and functions */
 int RME96_AR_ANALOG ; 
 int RME96_AR_BITPOS_F0 ; 
 int RME96_AR_BITPOS_F1 ; 
 int RME96_AR_BITPOS_F2 ; 
 scalar_t__ RME96_IO_CONTROL_REGISTER ; 
 int RME96_RCR_BITPOS_F0 ; 
 int RME96_RCR_BITPOS_F1 ; 
 int RME96_RCR_BITPOS_F2 ; 
 int RME96_RCR_LOCK ; 
 int RME96_RCR_T_OUT ; 
 int RME96_RCR_VERF ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static int
snd_rme96_capture_getrate(struct rme96 *rme96,
			  int *is_adat)
{	
	int n, rate;

	*is_adat = 0;
	if (rme96->areg & RME96_AR_ANALOG) {
		/* Analog input, overrides S/PDIF setting */
		n = ((rme96->areg >> RME96_AR_BITPOS_F0) & 1) +
			(((rme96->areg >> RME96_AR_BITPOS_F1) & 1) << 1);
		switch (n) {
		case 1:
			rate = 32000;
			break;
		case 2:
			rate = 44100;
			break;
		case 3:
			rate = 48000;
			break;
		default:
			return -1;
		}
		return (rme96->areg & RME96_AR_BITPOS_F2) ? rate << 1 : rate;
	}

	rme96->rcreg = readl(rme96->iobase + RME96_IO_CONTROL_REGISTER);
	if (rme96->rcreg & RME96_RCR_LOCK) {
		/* ADAT rate */
		*is_adat = 1;
		if (rme96->rcreg & RME96_RCR_T_OUT) {
			return 48000;
		}
		return 44100;
	}

	if (rme96->rcreg & RME96_RCR_VERF) {
		return -1;
	}
	
	/* S/PDIF rate */
	n = ((rme96->rcreg >> RME96_RCR_BITPOS_F0) & 1) +
		(((rme96->rcreg >> RME96_RCR_BITPOS_F1) & 1) << 1) +
		(((rme96->rcreg >> RME96_RCR_BITPOS_F2) & 1) << 2);
	
	switch (n) {
	case 0:		
		if (rme96->rcreg & RME96_RCR_T_OUT) {
			return 64000;
		}
		return -1;
	case 3: return 96000;
	case 4: return 88200;
	case 5: return 48000;
	case 6: return 44100;
	case 7: return 32000;
	default:
		break;
	}
	return -1;
}