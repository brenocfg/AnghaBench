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
typedef  int /*<<< orphan*/  in_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int inet_pton (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 

in_addr_t inet_addr(const char *cp) {
  in_addr_t ret;
  if (inet_pton(AF_INET, cp, &ret) != 1) {
    return 0;
  }

  return ret;
}