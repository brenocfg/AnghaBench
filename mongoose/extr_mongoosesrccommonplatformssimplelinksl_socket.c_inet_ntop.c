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
struct in_addr {int /*<<< orphan*/  s_addr; } ;
typedef  int /*<<< orphan*/  socklen_t ;

/* Variables and functions */
 int AF_INET ; 
 int /*<<< orphan*/  ENOTSUP ; 
 int /*<<< orphan*/  SL_IPV4_BYTE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  errno ; 
 int snprintf (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

const char *inet_ntop(int af, const void *src, char *dst, socklen_t size) {
  int res;
  struct in_addr *in = (struct in_addr *) src;
  if (af != AF_INET) {
    errno = ENOTSUP;
    return NULL;
  }
  res = snprintf(dst, size, "%lu.%lu.%lu.%lu", SL_IPV4_BYTE(in->s_addr, 0),
                 SL_IPV4_BYTE(in->s_addr, 1), SL_IPV4_BYTE(in->s_addr, 2),
                 SL_IPV4_BYTE(in->s_addr, 3));
  return res > 0 ? dst : NULL;
}