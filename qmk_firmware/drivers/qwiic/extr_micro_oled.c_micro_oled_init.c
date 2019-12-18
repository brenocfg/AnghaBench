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
 int CHARGEPUMP ; 
 int COMSCANDEC ; 
 int COMSCANINC ; 
 int DISPLAYALLONRESUME ; 
 int DISPLAYOFF ; 
 int DISPLAYON ; 
 int /*<<< orphan*/  I2C_ADDRESS_SA0_1 ; 
 int LCDHEIGHT ; 
 int MEMORYMODE ; 
 int NORMALDISPLAY ; 
 int SEGREMAP ; 
 int SETCOMPINS ; 
 int SETCONTRAST ; 
 int SETDISPLAYCLOCKDIV ; 
 int SETDISPLAYOFFSET ; 
 int SETMULTIPLEX ; 
 int SETPRECHARGE ; 
 int SETSTARTLINE ; 
 int SETVCOMDESELECT ; 
 int /*<<< orphan*/  clear_screen () ; 
 int /*<<< orphan*/  i2c_init () ; 
 int /*<<< orphan*/  i2c_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_buffer () ; 
 int /*<<< orphan*/  send_command (int) ; 

void micro_oled_init(void) {
    i2c_init();
    i2c_start(I2C_ADDRESS_SA0_1);

    // Display Init sequence for 64x48 OLED module
    send_command(DISPLAYOFF);  // 0xAE

    send_command(SETDISPLAYCLOCKDIV);  // 0xD5
    send_command(0x80);                // the suggested ratio 0x80

    send_command(SETMULTIPLEX);  // 0xA8
    send_command(LCDHEIGHT - 1);

    send_command(SETDISPLAYOFFSET);  // 0xD3
    send_command(0x00);              // no offset

    send_command(SETSTARTLINE | 0x00);  // line #0

    send_command(CHARGEPUMP);  // enable charge pump
    send_command(0x14);

    send_command(NORMALDISPLAY);       // 0xA6
    send_command(DISPLAYALLONRESUME);  // 0xA4

    // display at regular orientation
    send_command(SEGREMAP | 0x1);
    send_command(COMSCANDEC);

// rotate display 180
#ifdef micro_oled_rotate_180
    send_command(SEGREMAP);
    send_command(COMSCANINC);
#endif

    send_command(MEMORYMODE);
    send_command(0x10);

    send_command(SETCOMPINS);  // 0xDA
    if (LCDHEIGHT > 32) {
        send_command(0x12);
    } else {
        send_command(0x02);
    }
    send_command(SETCONTRAST);  // 0x81
    send_command(0x8F);

    send_command(SETPRECHARGE);  // 0xd9
    send_command(0xF1);

    send_command(SETVCOMDESELECT);  // 0xDB
    send_command(0x40);

    send_command(DISPLAYON);  //--turn on oled panel
    clear_screen();           // Erase hardware memory inside the OLED controller to avoid random data in memory.
    send_buffer();
}