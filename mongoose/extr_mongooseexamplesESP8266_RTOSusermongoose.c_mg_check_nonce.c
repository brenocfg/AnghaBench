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

/* Variables and functions */
 scalar_t__ mg_time () ; 
 scalar_t__ strtoul (char const*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int mg_check_nonce(const char *nonce) {
  unsigned long now = (unsigned long) mg_time();
  unsigned long val = (unsigned long) strtoul(nonce, NULL, 16);
  return (now >= val) && (now - val < 60 * 60);
}