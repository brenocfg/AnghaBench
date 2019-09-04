#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct TYPE_3__ {scalar_t__ NVM_Signature; scalar_t__ NVM_CheckSum; } ;

/* Variables and functions */
 scalar_t__ INI_SIGNATURE ; 
 TYPE_1__ i91unvram ; 
 TYPE_1__* i91unvramp ; 
 int /*<<< orphan*/  initio_se2_rd (unsigned long,int) ; 

__attribute__((used)) static int initio_se2_rd_all(unsigned long base)
{
	int i;
	u16 chksum = 0;
	u16 *np;

	i91unvramp = &i91unvram;
	np = (u16 *) i91unvramp;
	for (i = 0; i < 32; i++)
		*np++ = initio_se2_rd(base, i);

	/* Is signature "ini" ok ? */
	if (i91unvramp->NVM_Signature != INI_SIGNATURE)
		return -1;
	/* Is ckecksum ok ? */
	np = (u16 *) i91unvramp;
	for (i = 0; i < 31; i++)
		chksum += *np++;
	if (i91unvramp->NVM_CheckSum != chksum)
		return -1;
	return 1;
}