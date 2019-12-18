#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
struct TYPE_4__ {void* h; void* v; void* y; void* x; } ;
typedef  TYPE_1__ report_mouse_t ;
typedef  void* int8_t ;

/* Variables and functions */
 int LOWER_ROWMASK ; 
 int MAIN_ROWMASK ; 
 int MATRIX_ROWS ; 
 int SERIAL_UART_DATA ; 
 int /*<<< orphan*/  SERIAL_UART_INIT () ; 
 int /*<<< orphan*/  SERIAL_UART_RXD_PRESENT ; 
 int bitrev16 (int) ; 
 int* matrix ; 
 int /*<<< orphan*/  matrix_scan_quantum () ; 
 TYPE_1__ pointing_device_get_report () ; 
 int /*<<< orphan*/  pointing_device_set_report (TYPE_1__) ; 
 int /*<<< orphan*/  xprintf (char*) ; 

uint8_t matrix_scan(void)
{
    SERIAL_UART_INIT();
    //xprintf("\r\nTRYING TO SCAN");

    uint32_t timeout = 0;

    //the s character requests the RF slave to send the matrix
    SERIAL_UART_DATA = 's';

    //trust the external keystates entirely, erase the last data
    uint8_t uart_data[11] = {0};

    //there are 10 bytes corresponding to 10 columns, and an end byte
    for (uint8_t i = 0; i < 11; i++) {
        //wait for the serial data, timeout if it's been too long
        //this only happened in testing with a loose wire, but does no
        //harm to leave it in here
        while(!SERIAL_UART_RXD_PRESENT){
            timeout++;
            if (timeout > 10000){
		xprintf("\r\nTime out in keyboard.");
                break;
            }
        }
        uart_data[i] = SERIAL_UART_DATA;
    }

    //check for the end packet, the key state bytes use the LSBs, so 0xE0
    //will only show up here if the correct bytes were recieved
            uint8_t checksum = 0x00;
            for (uint8_t z=0; z<10; z++){
                checksum = checksum^uart_data[z];
            }
            checksum = checksum ^ (uart_data[10] & 0xF0);
            // Smash the checksum from 1 byte into 4 bits
            checksum = (checksum ^ ((checksum & 0xF0)>>4)) & 0x0F;
//xprintf("\r\nGOT RAW PACKET: \r\n%d\r\n%d\r\n%d\r\n%d\r\n%d\r\n%d\r\n%d\r\n%d\r\n%d\r\n%d\r\n%d\r\n%d",uart_data[0],uart_data[1],uart_data[2],uart_data[3],uart_data[4],uart_data[5],uart_data[6],uart_data[7],uart_data[8],uart_data[9],uart_data[10],checksum);
    if ((uart_data[10] & 0x0F) == checksum) { //this is an arbitrary binary checksum (1001) (that would be 0x9.)
	//xprintf("\r\nGOT PACKET: \r\n%d\r\n%d\r\n%d\r\n%d\r\n%d\r\n%d",uart_data[0],uart_data[1],uart_data[2],uart_data[3],uart_data[4],uart_data[5]);
        //shifting and transferring the keystates to the QMK matrix variable
		//bits 1-12 are row 1, 13-24 are row 2, 25-36 are row 3,
		//bits 37-42 are row 4 (only 6 wide, 1-3 are 0, and 10-12 are 0)
		//bits 43-48 are row 5 (same as row 4)
		/* ASSUMING MSB FIRST */
		matrix[0] = (((uint16_t) uart_data[0] << 8) | ((uint16_t) uart_data[1])) & MAIN_ROWMASK;
		matrix[1] = ((uint16_t) uart_data[1] << 12) | ((uint16_t) uart_data[2] << 4);
		matrix[2] = (((uint16_t) uart_data[3] << 8) | ((uint16_t) uart_data[4])) & MAIN_ROWMASK;
		matrix[3] = (((uint16_t) uart_data[4] << 9) | ((uint16_t) uart_data[5] << 1)) & LOWER_ROWMASK;
		matrix[4] = (((uint16_t) uart_data[5] << 7) | ((uart_data[10] & 1<<7) ? 1:0) << 13 | ((uart_data[10] & 1<<6) ? 1:0) << 6) & LOWER_ROWMASK;
		/* OK, TURNS OUT THAT WAS A BAD ASSUMPTION */
        for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
			//I've unpacked these into the mirror image of what QMK expects them to be, so...
			/*uint8_t halfOne = (matrix[i]>>8);
			uint8_t halfTwo = (matrix[i] & 0xFF);
			halfOne = ((halfOne * 0x0802LU & 0x22110LU) | (halfOne * 0x8020LU & 0x88440LU)) * 0x10101LU >> 16;
			halfTwo = ((halfTwo * 0x0802LU & 0x22110LU) | (halfTwo * 0x8020LU & 0x88440LU)) * 0x10101LU >> 16;
			matrix[i] = ((halfTwo<<8) & halfOne);*/
			//matrix[i] = ((matrix[i] * 0x0802LU & 0x22110LU) | (matrix[i] * 0x8020LU & 0x88440LU)) * 0x10101LU >> 16;
			matrix[i] = bitrev16(matrix[i]);
			//bithack mirror!  Doesn't make any sense, but works - and efficiently.
        }
	//if (uart_data[6]!=0 || uart_data[7]!=0){
	//if (maxCount<101){
	//	xprintf("\r\nMouse data: x=%d, y=%d",(int8_t)uart_data[6],(int8_t)uart_data[7]);
	//}
	report_mouse_t currentReport = {};
        //check for the end packet, bytes 1-4 are movement and scroll
        //but byte 5 has bits 0-3 for the scroll button state
	//(1000 if pressed, 0000 if not) and bits 4-7 are always 1
	//We can use this to verify the report sent properly.

	currentReport = pointing_device_get_report();
        //shifting and transferring the info to the mouse report varaible
        //mouseReport.x = 127 max -127 min
	currentReport.x = (int8_t) uart_data[6];
        //mouseReport.y = 127 max -127 min
	currentReport.y = (int8_t) uart_data[7];
        //mouseReport.v = 127 max -127 min (scroll vertical)
	currentReport.v = (int8_t) uart_data[8];
        //mouseReport.h = 127 max -127 min (scroll horizontal)
	currentReport.h = (int8_t) uart_data[9];
	/*
	currentReport.x = 0;
	currentReport.y = 0;
	currentReport.v = 0;
	currentReport.h = 0;*/
	pointing_device_set_report(currentReport);
    } else {
	//xprintf("\r\nRequested packet, data 10 was %d but checksum was %d",(uart_data[10] & 0x0F), (checksum & 0x0F));
    }
    //matrix_print();

    matrix_scan_quantum();
    return 1;
}