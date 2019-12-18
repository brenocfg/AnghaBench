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
typedef  size_t uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  DCD_PIN ; 
 size_t MATRIX_ROWS ; 
 scalar_t__ PinLevelHigh ; 
 int /*<<< orphan*/  VCC_PIN ; 
 int /*<<< orphan*/  _delay_ms (int) ; 
 int debug_enable ; 
 scalar_t__ digitalRead (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  digitalWrite (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ handspring_handshake () ; 
 int /*<<< orphan*/  last_activity ; 
 int* matrix ; 
 int /*<<< orphan*/  matrix_init_quantum () ; 
 scalar_t__ palm_handshake () ; 
 int /*<<< orphan*/  pins_init () ; 
 int /*<<< orphan*/  print (char*) ; 
 int /*<<< orphan*/  rts_reset () ; 
 int /*<<< orphan*/  serial_init () ; 
 int /*<<< orphan*/  timer_read () ; 

void matrix_init(void)
{
    debug_enable = true;
    //debug_matrix =true;
    
    serial_init(); // arguments all #defined 
 
#if (HANDSPRING == 0)
    pins_init(); // set all inputs and outputs. 
#endif

    print("power up\n");
    digitalWrite(VCC_PIN, PinLevelHigh);

    // wait for DCD strobe from keyboard - it will do this 
    // up to 3 times, then the board needs the RTS toggled to try again
  
#if ( HANDSPRING == 1)
    if ( handspring_handshake() ) {
        last_activity = timer_read();
    } else { 
        print("failed handshake");
        _delay_ms(1000);
        //BUG /should/ power cycle or toggle RTS & reset, but this usually works. 
    }

#else  /// Palm / HP  device with DCD
    while( digitalRead(DCD_PIN) != PinLevelHigh ) {;} 
    print("dcd\n");

    rts_reset(); // at this point the keyboard should think all is well. 

    if ( palm_handshake() ) {
        last_activity = timer_read();
    } else { 
        print("failed handshake");
        _delay_ms(1000);
        //BUG /should/ power cycle or toggle RTS & reset, but this usually works. 
    }

#endif

    // initialize matrix state: all keys off
    for (uint8_t i=0; i < MATRIX_ROWS; i++) matrix[i] = 0x00;

    matrix_init_quantum();
    return;
    
    
}