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
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  TCS34725_ENABLE ; 
 int TCS34725_ENABLE_AEN ; 
 int TCS34725_ENABLE_PON ; 
 int _tcs34725Initialised ; 
 int tcs34725Read8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcs34725Write8 (int /*<<< orphan*/ ,int) ; 

uint8_t tcs34725Disable(lua_State* L)
{
	/* Turn the device off to save power */
	uint8_t reg = 0;
	reg = tcs34725Read8(TCS34725_ENABLE);
	tcs34725Write8(TCS34725_ENABLE, reg & ~(TCS34725_ENABLE_PON | TCS34725_ENABLE_AEN));
	_tcs34725Initialised = false;
	return 0;
}