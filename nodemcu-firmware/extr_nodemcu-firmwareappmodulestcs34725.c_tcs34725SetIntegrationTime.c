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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  tcs34725IntegrationTime_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  TCS34725_ATIME ; 
 int /*<<< orphan*/  _tcs34725Initialised ; 
 int /*<<< orphan*/  _tcs34725IntegrationTime ; 
 int /*<<< orphan*/  tcs34725Setup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcs34725Write8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

uint8_t tcs34725SetIntegrationTime(tcs34725IntegrationTime_t it, lua_State* L)
{
	if (!_tcs34725Initialised)
	{
		tcs34725Setup(L);
	}

	tcs34725Write8(TCS34725_ATIME, it);
	_tcs34725IntegrationTime = it;

	return 0;
}