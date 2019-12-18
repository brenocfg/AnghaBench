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
typedef  int uint8_t ;

/* Variables and functions */
#define  KC_DEL 135 
#define  KC_END 134 
#define  KC_H 133 
#define  KC_HOME 132 
#define  KC_INSERT 131 
#define  KC_PGDOWN 130 
#define  KC_PGUP 129 
#define  KC_SLASH 128 
 int /*<<< orphan*/  print (char*) ; 
 int /*<<< orphan*/  serial_send (int) ; 
 int sun_bell ; 
 int sun_click ; 
 int /*<<< orphan*/  xprintf (char*,int) ; 

bool command_extra(uint8_t code)
{
    switch (code) {
        case KC_H:
        case KC_SLASH: /* ? */
            print("\n\n----- Sun converter Help -----\n");
            print("Home:        Toggle Bell\n");
            print("End:         Toggle Click\n");
            print("PgUp:        LED all On\n");
            print("PgDown:      LED all Off\n");
            print("Insert:      Layout\n");
            print("Delete:      Reset\n");
            return false;
        case KC_DEL:
            print("Reset\n");
            serial_send(0x01);
            break;
        case KC_HOME:
	    sun_bell = !sun_bell;
	    if (sun_bell) {
                print("Bell On\n");
	        serial_send(0x02);
	    } else {
	        print("Bell Off\n");
	        serial_send(0x03);
	    }
            break;
        case KC_END:
	    sun_click = !sun_click;
	    if (sun_click) {
	        print("Click On\n");
		serial_send(0x0A);
	    } else {
	        print("Click Off\n");
                serial_send(0x0B);
	    }
	    break;
        case KC_PGUP:
            print("LED all on\n");
            serial_send(0x0E);
            serial_send(0xFF);
            break;
        case KC_PGDOWN:
            print("LED all off\n");
            serial_send(0x0E);
            serial_send(0x00);
            break;
        case KC_INSERT:
            print("layout\n");
            serial_send(0x0F);
            break;
        default:
            xprintf("Unknown extra command: %02X\n", code);
            return false;
    }
    return true;
}