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
typedef  int u8_t ;
typedef  int /*<<< orphan*/  u32_t ;
typedef  int /*<<< orphan*/  ip_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ip4_addr_get_u32 (int /*<<< orphan*/  const*) ; 

char *ipaddr_ntoa_r(const ip_addr_t *addr, char *buf, int buflen)
{
  u32_t s_addr;
  char inv[3];
  char *rp;
  u8_t *ap;
  u8_t rem;
  u8_t n;
  u8_t i;
  int len = 0;

  s_addr = ip4_addr_get_u32(addr);

  rp = buf;
  ap = (u8_t *)&s_addr;
  for(n = 0; n < 4; n++) {
    i = 0;
    do {
      rem = *ap % (u8_t)10;
      *ap /= (u8_t)10;
      inv[i++] = '0' + rem;
    } while(*ap);
    while(i--) {
      if (len++ >= buflen) {
        return NULL;
      }
      *rp++ = inv[i];
    }
    if (len++ >= buflen) {
      return NULL;
    }
    *rp++ = '.';
    ap++;
  }
  *--rp = 0;
  return buf;
}