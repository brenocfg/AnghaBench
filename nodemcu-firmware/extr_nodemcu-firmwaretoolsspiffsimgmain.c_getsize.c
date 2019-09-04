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
 size_t strtoul (char const*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t getsize(const char *s)
{
  char *end = 0;
  size_t val = strtoul(s, &end, 0);

  if (end) {
    int factor;
    if (*end == 'k' || *end == 'K') {
      factor = 1 << 10;
      end++;
    } else if (*end == 'm' || *end == 'M') {
      factor = 1 << 20;
      end++;
    } else {
      factor = 1;
    }
    // Capital B is bytes
    if (*end == 'B') {
      factor = factor << 3;
    }
    // we want bytes
    val = (val * factor) / 8;
  }

  return val;
}