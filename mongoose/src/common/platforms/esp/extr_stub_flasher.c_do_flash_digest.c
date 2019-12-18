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
typedef  int /*<<< orphan*/  digest ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int FLASH_SECTOR_SIZE ; 
 int /*<<< orphan*/  MD5Final (int /*<<< orphan*/ *,struct MD5Context*) ; 
 int /*<<< orphan*/  MD5Init (struct MD5Context*) ; 
 int /*<<< orphan*/  MD5Update (struct MD5Context*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ esp_rom_spiflash_read (int,int*,int) ; 
 int /*<<< orphan*/  send_packet (int /*<<< orphan*/ *,int) ; 

int do_flash_digest(uint32_t addr, uint32_t len, uint32_t digest_block_size) {
  uint8_t buf[FLASH_SECTOR_SIZE];
  uint8_t digest[16];
  uint32_t read_block_size =
      digest_block_size ? digest_block_size : sizeof(buf);
  struct MD5Context ctx;
  if (digest_block_size > sizeof(buf)) return 0x62;
  MD5Init(&ctx);
  while (len > 0) {
    uint32_t n = len;
    struct MD5Context block_ctx;
    MD5Init(&block_ctx);
    if (n > read_block_size) n = read_block_size;
    if (esp_rom_spiflash_read(addr, (uint32_t *) buf, n) != 0) return 0x63;
    MD5Update(&ctx, buf, n);
    if (digest_block_size > 0) {
      MD5Update(&block_ctx, buf, n);
      MD5Final(digest, &block_ctx);
      send_packet(digest, sizeof(digest));
    }
    addr += n;
    len -= n;
  }
  MD5Final(digest, &ctx);
  send_packet(digest, sizeof(digest));
  return 0;
}