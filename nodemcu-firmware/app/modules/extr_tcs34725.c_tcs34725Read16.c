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
typedef  int uint16_t ;

/* Variables and functions */
 int tcs34725Read8 (int) ; 

uint16_t tcs34725Read16(uint8_t reg)
{
	uint8_t low = tcs34725Read8(reg);
	uint8_t high = tcs34725Read8(++reg);

	return (high << 8) | low;
}