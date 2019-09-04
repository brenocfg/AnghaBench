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
struct sym_fw {int dummy; } ;
struct sym_chip {int features; } ;

/* Variables and functions */
 int FE_LDSTR ; 
 struct sym_fw sym_fw2 ; 

struct sym_fw * 
sym_find_firmware(struct sym_chip *chip)
{
	if (chip->features & FE_LDSTR)
		return &sym_fw2;
#if	SYM_CONF_GENERIC_SUPPORT
	else if (!(chip->features & (FE_PFEN|FE_NOPM|FE_DAC)))
		return &sym_fw1;
#endif
	else
		return NULL;
}