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
typedef  int u8 ;
struct mtpav {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CREG ; 
 int /*<<< orphan*/  DREG ; 
 int SIGC_WRITE ; 
 int snd_mtpav_getreg (struct mtpav*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mtpav_mputreg (struct mtpav*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_mtpav_wait_rfdhi (struct mtpav*) ; 

__attribute__((used)) static void snd_mtpav_send_byte(struct mtpav *chip, u8 byte)
{
	u8 tcbyt;
	u8 clrwrite;
	u8 setwrite;

	snd_mtpav_wait_rfdhi(chip);

	/////////////////

	tcbyt = snd_mtpav_getreg(chip, CREG);
	clrwrite = tcbyt & (SIGC_WRITE ^ 0xff);
	setwrite = tcbyt | SIGC_WRITE;

	snd_mtpav_mputreg(chip, DREG, byte);
	snd_mtpav_mputreg(chip, CREG, clrwrite);	// clear write bit

	snd_mtpav_mputreg(chip, CREG, setwrite);	// set write bit

}