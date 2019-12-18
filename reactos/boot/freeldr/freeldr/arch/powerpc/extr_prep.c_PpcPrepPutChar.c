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
 int /*<<< orphan*/  SetPhysByte (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  prep_serial ; 
 int /*<<< orphan*/  sync () ; 

void PpcPrepPutChar( int ch ) {
    if( ch == 0x0a ) {
    SetPhysByte(prep_serial, 0x0d);
    sync();
    }
    SetPhysByte(prep_serial, ch);
    sync();
}