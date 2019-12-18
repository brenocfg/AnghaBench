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
 int /*<<< orphan*/  ofw_write (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout_handle ; 
 int /*<<< orphan*/  strlen (char*) ; 

void PpcOfwPutChar( int ch ) {
    char buf[3];
    if( ch == 0x0a ) { buf[0] = 0x0d; buf[1] = 0x0a; }
    else { buf[0] = ch; buf[1] = 0; }
    buf[2] = 0;
    ofw_write(stdout_handle, buf, strlen(buf));
}