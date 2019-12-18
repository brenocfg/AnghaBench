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
typedef  int uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  serial_send (int) ; 
 int usage2bits (int) ; 

__attribute__((used)) static void send_consumer(uint16_t data)
{
    uint16_t bits = usage2bits(data);
    serial_send(0xFD);  // Raw report mode
    serial_send(3);     // length
    serial_send(3);     // descriptor type
    serial_send(bits&0xFF);
    serial_send((bits>>8)&0xFF);
}