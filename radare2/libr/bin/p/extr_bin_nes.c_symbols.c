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
typedef  int /*<<< orphan*/  RList ;
typedef  int /*<<< orphan*/  RBinFile ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_VECTOR_START_ADDRESS ; 
 int /*<<< orphan*/  JOYPAD_PORT ; 
 int /*<<< orphan*/  JOYPAD_PORT1 ; 
 int /*<<< orphan*/  JOYPAD_PORT2 ; 
 int /*<<< orphan*/  NMI_VECTOR_START_ADDRESS ; 
 int /*<<< orphan*/  PPU_ADDRESS ; 
 int /*<<< orphan*/  PPU_CTRL_REG1 ; 
 int /*<<< orphan*/  PPU_CTRL_REG2 ; 
 int /*<<< orphan*/  PPU_DATA ; 
 int /*<<< orphan*/  PPU_SCROLL_REG ; 
 int /*<<< orphan*/  PPU_SPR_ADDR ; 
 int /*<<< orphan*/  PPU_SPR_DATA ; 
 int /*<<< orphan*/  PPU_STATUS ; 
 int /*<<< orphan*/  RESET_VECTOR_START_ADDRESS ; 
 int /*<<< orphan*/  SND_DELTA_REG ; 
 int /*<<< orphan*/  SND_MASTERCTRL_REG ; 
 int /*<<< orphan*/  SND_NOISE_REG ; 
 int /*<<< orphan*/  SND_REGISTER ; 
 int /*<<< orphan*/  SND_SQUARE1_REG ; 
 int /*<<< orphan*/  SND_SQUARE2_REG ; 
 int /*<<< orphan*/  SND_TRIANGLE_REG ; 
 int /*<<< orphan*/  SPR_DMA ; 
 int /*<<< orphan*/  addsym (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free ; 
 int /*<<< orphan*/ * r_list_newf (int /*<<< orphan*/ ) ; 

__attribute__((used)) static RList* symbols(RBinFile *bf) {
	RList *ret = NULL;
	if (!(ret = r_list_newf (free))) {
		return NULL;
	}
	addsym (ret, "NMI_VECTOR_START_ADDRESS", NMI_VECTOR_START_ADDRESS,2);
	addsym (ret, "RESET_VECTOR_START_ADDRESS", RESET_VECTOR_START_ADDRESS,2);
	addsym (ret, "IRQ_VECTOR_START_ADDRESS", IRQ_VECTOR_START_ADDRESS,2);
	addsym (ret, "PPU_CTRL_REG1", PPU_CTRL_REG1,0x1);
	addsym (ret, "PPU_CTRL_REG2", PPU_CTRL_REG2,0x1);
	addsym (ret, "PPU_STATUS", PPU_STATUS,0x1);
	addsym (ret, "PPU_SPR_ADDR", PPU_SPR_ADDR,0x1);
	addsym (ret, "PPU_SPR_DATA", PPU_SPR_DATA,0x1);
	addsym (ret, "PPU_SCROLL_REG", PPU_SCROLL_REG,0x1);
	addsym (ret, "PPU_ADDRESS", PPU_ADDRESS,0x1);
	addsym (ret, "PPU_DATA", PPU_DATA,0x1);
	addsym (ret, "SND_REGISTER", SND_REGISTER,0x15);
	addsym (ret, "SND_SQUARE1_REG", SND_SQUARE1_REG,0x4);
	addsym (ret, "SND_SQUARE2_REG", SND_SQUARE2_REG,0x4);
	addsym (ret, "SND_TRIANGLE_REG", SND_TRIANGLE_REG,0x4);
	addsym (ret, "SND_NOISE_REG", SND_NOISE_REG,0x2);
	addsym (ret, "SND_DELTA_REG", SND_DELTA_REG,0x4);
	addsym (ret, "SND_MASTERCTRL_REG", SND_MASTERCTRL_REG,0x5);
	addsym (ret, "SPR_DMA", SPR_DMA,0x2);
	addsym (ret, "JOYPAD_PORT", JOYPAD_PORT,0x1);
	addsym (ret, "JOYPAD_PORT1", JOYPAD_PORT1,0x1);
	addsym (ret, "JOYPAD_PORT2", JOYPAD_PORT2,0x1);
	return ret;
}