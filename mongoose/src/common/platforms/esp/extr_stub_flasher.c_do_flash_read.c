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
typedef  int uint32_t ;
struct MD5Context {int dummy; } ;
typedef  int /*<<< orphan*/  num_acked ;
typedef  int /*<<< orphan*/  digest ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int FLASH_SECTOR_SIZE ; 
 int /*<<< orphan*/  MD5Final (int /*<<< orphan*/ *,struct MD5Context*) ; 
 int /*<<< orphan*/  MD5Init (struct MD5Context*) ; 
 int /*<<< orphan*/  MD5Update (struct MD5Context*,int /*<<< orphan*/ *,int) ; 
 int SLIP_recv (int*,int) ; 
 scalar_t__ esp_rom_spiflash_read (int,int*,int) ; 
 int /*<<< orphan*/  send_packet (int /*<<< orphan*/ *,int) ; 

int do_flash_read(uint32_t addr, uint32_t len, uint32_t block_size,
                  uint32_t max_in_flight) {
  uint8_t buf[FLASH_SECTOR_SIZE];
  uint8_t digest[16];
  struct MD5Context ctx;
  uint32_t num_sent = 0, num_acked = 0;
  if (block_size > sizeof(buf)) return 0x52;
  MD5Init(&ctx);
  while (num_acked < len) {
    while (num_sent < len && num_sent - num_acked < max_in_flight) {
      uint32_t n = len - num_sent;
      if (n > block_size) n = block_size;
      if (esp_rom_spiflash_read(addr, (uint32_t *) buf, n) != 0) return 0x53;
      send_packet(buf, n);
      MD5Update(&ctx, buf, n);
      addr += n;
      num_sent += n;
    }
    {
      if (SLIP_recv(&num_acked, sizeof(num_acked)) != 4) return 0x54;
      if (num_acked > num_sent) return 0x55;
    }
  }
  MD5Final(digest, &ctx);
  send_packet(digest, sizeof(digest));
  return 0;
}