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
typedef  unsigned long u8_t ;
typedef  unsigned long u32_t ;
typedef  int /*<<< orphan*/  ip_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  LWIP_ASSERT (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htonl (unsigned long) ; 
 int /*<<< orphan*/  ip4_addr_set_u32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ isdigit (char) ; 
 scalar_t__ islower (char) ; 
 int /*<<< orphan*/  isspace (char) ; 
 scalar_t__ isxdigit (char) ; 

int
ipaddr_aton(const char *cp, ip_addr_t *addr)
{
  u32_t val;
  u8_t base;
  char c;
  char ch;
  unsigned long cutoff;
  int cutlim;
  u32_t parts[4];
  u32_t *pp = parts;

  c = *cp;
  for (;;) {
    /*
     * Collect number up to ``.''.
     * Values are specified as for C:
     * 0x=hex, 0=octal, 1-9=decimal.
     */
    if (!isdigit(c))
      return (0);
    val = 0;
    base = 10;
    if (c == '0') {
      c = *++cp;
      if (c == 'x' || c == 'X') {
        base = 16;
        c = *++cp;
      } else
        base = 8;
    }

    cutoff =(unsigned long)0xffffffff / (unsigned long)base;
    cutlim =(unsigned long)0xffffffff % (unsigned long)base;

    for (;;) {
      if (isdigit(c)) {
    	ch = (int)(c - '0');

    	if (val > cutoff || (val == cutoff && ch > cutlim))
    		return (0);

        val = (val * base) + (int)(c - '0');
        c = *++cp;
      } else if (base == 16 && isxdigit(c)) {
    	ch = (int)(c + 10 - (islower(c) ? 'a' : 'A'));

    	if (val > cutoff || (val == cutoff && ch > cutlim))
    		return (0);

    	val = (val << 4) | (int)(c + 10 - (islower(c) ? 'a' : 'A'));
        c = *++cp;
      } else
        break;
    }
    if (c == '.') {
      /*
       * Internet format:
       *  a.b.c.d
       *  a.b.c   (with c treated as 16 bits)
       *  a.b (with b treated as 24 bits)
       */
      if (pp >= parts + 3) {
        return (0);
      }
      *pp++ = val;
      c = *++cp;
    } else
      break;
  }
  /*
   * Check for trailing characters.
   */
  if (c != '\0' && !isspace(c)) {
    return (0);
  }
  /*
   * Concoct the address according to
   * the number of parts specified.
   */
  switch (pp - parts + 1) {

  case 0:
    return (0);       /* initial nondigit */

  case 1:             /* a -- 32 bits */
    break;

  case 2:             /* a.b -- 8.24 bits */
    if ((val > 0xffffffUL) || (parts[0] > 0xff)) {
      return (0);
    }
    val |= parts[0] << 24;
    break;

  case 3:             /* a.b.c -- 8.8.16 bits */
    if ((val > 0xffff) || (parts[0] > 0xff) || (parts[1] > 0xff)) {
      return (0);
    }
    val |= (parts[0] << 24) | (parts[1] << 16);
    break;

  case 4:             /* a.b.c.d -- 8.8.8.8 bits */
    if ((val > 0xff) || (parts[0] > 0xff) || (parts[1] > 0xff) || (parts[2] > 0xff)) {
      return (0);
    }
    val |= (parts[0] << 24) | (parts[1] << 16) | (parts[2] << 8);
    break;
  default:
    LWIP_ASSERT("unhandled", 0);
    break;
  }
  if (addr) {
    ip4_addr_set_u32(addr, htonl(val));
  }
  return (1);
}