#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int mods; int* keys; } ;
typedef  TYPE_1__ report_keyboard_t ;

/* Variables and functions */
 int /*<<< orphan*/  serial_send (int) ; 

__attribute__((used)) static void send_keyboard(report_keyboard_t *report)
{
    // wake from deep sleep
/*
    PORTD |= (1<<5);    // high
    wait_ms(5);
    PORTD &= ~(1<<5);   // low
*/

    serial_send(0xFD);  // Raw report mode
    serial_send(9);     // length
    serial_send(1);     // descriptor type
    serial_send(report->mods);
    serial_send(0x00);
    serial_send(report->keys[0]);
    serial_send(report->keys[1]);
    serial_send(report->keys[2]);
    serial_send(report->keys[3]);
    serial_send(report->keys[4]);
    serial_send(report->keys[5]);
}