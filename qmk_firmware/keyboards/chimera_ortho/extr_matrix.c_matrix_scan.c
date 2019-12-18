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
typedef  int uint32_t ;
typedef  int uint16_t ;

/* Variables and functions */
 int MATRIX_ROWS ; 
 int SERIAL_UART_DATA ; 
 int /*<<< orphan*/  SERIAL_UART_INIT () ; 
 int /*<<< orphan*/  SERIAL_UART_RXD_PRESENT ; 
 int* matrix ; 
 int /*<<< orphan*/  matrix_scan_quantum () ; 

uint8_t matrix_scan(void)
{
    SERIAL_UART_INIT();

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
                break;
            }
        }
        uart_data[i] = SERIAL_UART_DATA;
    }

    //check for the end packet, the key state bytes use the LSBs, so 0xE0
    //will only show up here if the correct bytes were recieved
    if (uart_data[10] == 0xE0)
    {
        //shifting and transferring the keystates to the QMK matrix variable
        for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
            matrix[i] = (uint16_t) uart_data[i*2] | (uint16_t) uart_data[i*2+1] << 5;
        }
    }


    matrix_scan_quantum();
    return 1;
}