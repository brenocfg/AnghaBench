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
typedef  int u32 ;
struct phy_dm_struct {int dummy; } ;

/* Variables and functions */
 int MASKBYTE0 ; 
 int MASKBYTE1 ; 
 int MASKBYTE2 ; 
 int MASKBYTE3 ; 
 int /*<<< orphan*/  MASKDWORD ; 
 int /*<<< orphan*/  PHYDM_SNPRINTF (char*,int,char*,int,int,int,int,int,int,int,int) ; 
 int odm_get_bb_reg (struct phy_dm_struct*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  odm_set_bb_reg (struct phy_dm_struct*,int,int,int) ; 

__attribute__((used)) static inline void phydm_print_csi(struct phy_dm_struct *dm, u32 used,
				   u32 out_len, char *output)
{
	int index, ptr;
	u32 dword_h, dword_l;

	for (index = 0; index < 80; index++) {
		ptr = index + 256;

		if (ptr > 311)
			ptr -= 312;

		odm_set_bb_reg(dm, 0x1910, 0x03FF0000, ptr); /*Select Address*/
		dword_h = odm_get_bb_reg(dm, 0xF74, MASKDWORD);
		dword_l = odm_get_bb_reg(dm, 0xF5C, MASKDWORD);

		if (index % 2 == 0)
			PHYDM_SNPRINTF(
				output + used, out_len - used,
				"%02x  %02x  %02x  %02x  %02x  %02x  %02x  %02x\n",
				dword_l & MASKBYTE0, (dword_l & MASKBYTE1) >> 8,
				(dword_l & MASKBYTE2) >> 16,
				(dword_l & MASKBYTE3) >> 24,
				dword_h & MASKBYTE0, (dword_h & MASKBYTE1) >> 8,
				(dword_h & MASKBYTE2) >> 16,
				(dword_h & MASKBYTE3) >> 24);
		else
			PHYDM_SNPRINTF(
				output + used, out_len - used,
				"%02x  %02x  %02x  %02x  %02x  %02x  %02x  %02x\n",
				dword_l & MASKBYTE0, (dword_l & MASKBYTE1) >> 8,
				(dword_l & MASKBYTE2) >> 16,
				(dword_l & MASKBYTE3) >> 24,
				dword_h & MASKBYTE0, (dword_h & MASKBYTE1) >> 8,
				(dword_h & MASKBYTE2) >> 16,
				(dword_h & MASKBYTE3) >> 24);
	}
}