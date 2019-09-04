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
typedef  char uint8_t ;
typedef  int uint32 ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  init_data ;

/* Variables and functions */
 scalar_t__ SPI_FLASH_RESULT_OK ; 
 int SPI_FLASH_SEC_SIZE ; 
 scalar_t__ flash_erase (int) ; 
 scalar_t__ flash_read (int,int*,int) ; 
 int flash_rom_get_sec_num () ; 
 scalar_t__ flash_write (int,int*,int) ; 
 char luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_pushboolean (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int adc_init107( lua_State *L )
{
  uint8_t byte107 = luaL_checkinteger (L, 1);

  uint32 init_sector = flash_rom_get_sec_num () - 4;

  // Note 32bit alignment so we can safely cast to uint32 for the flash api
  char init_data[SPI_FLASH_SEC_SIZE] __attribute__((aligned(4)));

  if (SPI_FLASH_RESULT_OK != flash_read (
    init_sector * SPI_FLASH_SEC_SIZE,
    (uint32 *)init_data, sizeof(init_data)))
      return luaL_error(L, "flash read error");

  // If it's already the correct value, we don't need to force it
  if (init_data[107] == byte107)
  {
    lua_pushboolean (L, false);
    return 1;
  }

  // Nope, it differs, we need to rewrite it
  init_data[107] = byte107;
  if (SPI_FLASH_RESULT_OK != flash_erase (init_sector))
    return luaL_error(L, "flash erase error");

  if (SPI_FLASH_RESULT_OK != flash_write (
    init_sector * SPI_FLASH_SEC_SIZE,
    (uint32 *)init_data, sizeof(init_data)))
      return luaL_error(L, "flash write error");

  lua_pushboolean (L, true);
  return 1;
}