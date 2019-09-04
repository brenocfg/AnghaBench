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
struct rme96 {int areg; int wcreg; } ;

/* Variables and functions */
 int RME96_AR_ANALOG ; 
 int RME96_INPUT_ANALOG ; 
 int RME96_WCR_BITPOS_INP_0 ; 
 int RME96_WCR_BITPOS_INP_1 ; 

__attribute__((used)) static int
snd_rme96_getinputtype(struct rme96 *rme96)
{
	if (rme96->areg & RME96_AR_ANALOG) {
		return RME96_INPUT_ANALOG;
	}
	return ((rme96->wcreg >> RME96_WCR_BITPOS_INP_0) & 1) +
		(((rme96->wcreg >> RME96_WCR_BITPOS_INP_1) & 1) << 1);
}