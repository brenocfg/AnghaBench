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
 int COL (int) ; 
 scalar_t__ KEYUP (int) ; 
 size_t ROW (int) ; 
 scalar_t__ SLEEP_TIMEOUT ; 
 int /*<<< orphan*/  debug (char*) ; 
 int /*<<< orphan*/  debug_hex (int) ; 
 scalar_t__ disconnect_counter ; 
 int /*<<< orphan*/  handspring_reset () ; 
 int /*<<< orphan*/  last_activity ; 
 int last_upKey ; 
 int* matrix ; 
 scalar_t__ matrix_is_on (size_t,int) ; 
 int /*<<< orphan*/  matrix_scan_quantum () ; 
 int /*<<< orphan*/  palm_reset () ; 
 int /*<<< orphan*/  print (char*) ; 
 int serial_recv () ; 
 scalar_t__ timer_elapsed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_read () ; 

uint8_t matrix_scan(void)
{
    uint8_t code;
    code = serial_recv();
    if (!code) {
/*         
        disconnect_counter ++;
        if (disconnect_counter > MAXDROP) {
            //  set all keys off
             for (uint8_t i=0; i < MATRIX_ROWS; i++) matrix[i] = 0x00; 
        }
*/
        // check if the keyboard is asleep. 
        if (timer_elapsed(last_activity) > SLEEP_TIMEOUT) {
#if(HANDSPRING ==0 )
            palm_reset();
#else
            handspring_reset();
#endif
            return 0;
        } 

    }

   last_activity = timer_read();
   disconnect_counter=0; // if we are getting serial data, we're connected. 

    debug_hex(code); debug(" ");


    switch (code) {
        case 0xFD:  // unexpected reset byte 2
             print("rstD ");
            return 0;
        case 0xFA:  // unexpected reset
            print("rstA ");
            return 0;
    }

    if (KEYUP(code)) {
        if (code == last_upKey) {
            // all keys are not pressed. 
            // Manual says to disable all modifiers left open now. 
            // but that could defeat sticky keys. 
            // BUG? dropping this byte. 
            last_upKey=0;
            return 0;
        }
        // release
        if (matrix_is_on(ROW(code), COL(code))) {
            matrix[ROW(code)] &= ~(1<<COL(code));
            last_upKey=code;
        }
    } else {
       // press
        if (!matrix_is_on(ROW(code), COL(code))) {
            matrix[ROW(code)] |= (1<<COL(code));

        }
    }

    matrix_scan_quantum();
    return code;
}