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
typedef  int /*<<< orphan*/  value ;
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  args ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR_PERI_REG_MASK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  CMD_BOOT_FW 137 
#define  CMD_ECHO 136 
#define  CMD_FLASH_DIGEST 135 
#define  CMD_FLASH_ERASE_CHIP 134 
#define  CMD_FLASH_READ 133 
#define  CMD_FLASH_READ_CHIP_ID 132 
#define  CMD_FLASH_WRITE 131 
#define  CMD_READ_REG 130 
#define  CMD_REBOOT 129 
#define  CMD_WRITE_REG 128 
 int READ_PERI_REG (int*) ; 
 int /*<<< orphan*/  SET_PERI_REG_MASK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SLIP_recv (int*,int) ; 
 int /*<<< orphan*/  SLIP_send (int*,int) ; 
 int /*<<< orphan*/  UART_CONF0_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UART_RXFIFO_RST ; 
 int /*<<< orphan*/  WRITE_PERI_REG (int*,int) ; 
 int do_flash_digest (int,int,int) ; 
 int do_flash_read (int,int,int,int) ; 
 int do_flash_read_chip_id () ; 
 int do_flash_write (int,int,int) ; 
 int esp_rom_spiflash_erase_chip () ; 

uint8_t cmd_loop(void) {
  uint8_t cmd = 0x55;
  do {
    /* Reset FIFO to re-sync */
    SET_PERI_REG_MASK(UART_CONF0_REG(0), UART_RXFIFO_RST);
    CLEAR_PERI_REG_MASK(UART_CONF0_REG(0), UART_RXFIFO_RST);
    uint32_t args[4];
    uint32_t len = SLIP_recv(&cmd, 1);
    if (len != 1) {
      continue;
    }
    uint8_t resp = 0xff;
    switch (cmd) {
      case CMD_FLASH_WRITE: {
        len = SLIP_recv(args, sizeof(args));
        if (len == 12) {
          resp = do_flash_write(args[0] /* addr */, args[1] /* len */,
                                args[2] /* erase */);
        } else {
          resp = 0x41;
        }
        break;
      }
      case CMD_FLASH_READ: {
        len = SLIP_recv(args, sizeof(args));
        if (len == 16) {
          resp = do_flash_read(args[0] /* addr */, args[1], /* len */
                               args[2] /* block_size */,
                               args[3] /* max_in_flight */);
        } else {
          resp = 0x51;
        }
        break;
      }
      case CMD_FLASH_DIGEST: {
        len = SLIP_recv(args, sizeof(args));
        if (len == 12) {
          resp = do_flash_digest(args[0] /* addr */, args[1], /* len */
                                 args[2] /* digest_block_size */);
        } else {
          resp = 0x61;
        }
        break;
      }
      case CMD_FLASH_READ_CHIP_ID: {
        resp = do_flash_read_chip_id();
        break;
      }
      case CMD_FLASH_ERASE_CHIP: {
        resp = esp_rom_spiflash_erase_chip();
        break;
      }
      case CMD_BOOT_FW:
      case CMD_REBOOT: {
        resp = 0;
        SLIP_send(&resp, 1);
        return cmd;
      }
      case CMD_ECHO: {
        len = SLIP_recv(args, sizeof(args));
        SLIP_send(args, len);
        resp = 0;
        break;
      }
      case CMD_READ_REG: {
        len = SLIP_recv(args, sizeof(args));
        if (len == 4) {
          uint32_t value = READ_PERI_REG((uint32_t *) args[0]);
          SLIP_send(&value, sizeof(value));
          resp = 0;
        } else {
          resp = 0x91;
        }
        break;
      }
      case CMD_WRITE_REG: {
        len = SLIP_recv(args, sizeof(args));
        if (len == 8) {
          WRITE_PERI_REG((uint32_t *) args[0], args[1]);
          resp = 0;
        } else {
          resp = 0xa1;
        }
        break;
      }
    }
    SLIP_send(&resp, 1);
  } while (cmd != CMD_BOOT_FW && cmd != CMD_REBOOT);
  return cmd;
}