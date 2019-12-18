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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int AF_INET ; 
 int /*<<< orphan*/  ENOTSUP ; 
 int /*<<< orphan*/  errno ; 
 int sscanf (char const*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int inet_pton(int af, const char *src, void *dst) {
  uint32_t a0, a1, a2, a3;
  uint8_t *db = (uint8_t *) dst;
  if (af != AF_INET) {
    errno = ENOTSUP;
    return 0;
  }
  if (sscanf(src, "%lu.%lu.%lu.%lu", &a0, &a1, &a2, &a3) != 4) {
    return 0;
  }
  *db = a3;
  *(db + 1) = a2;
  *(db + 2) = a1;
  *(db + 3) = a0;
  return 1;
}