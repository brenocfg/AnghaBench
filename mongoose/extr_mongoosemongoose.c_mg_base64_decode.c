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
 int cs_base64_decode (unsigned char const*,int,char*,int /*<<< orphan*/ *) ; 

int mg_base64_decode(const unsigned char *s, int len, char *dst) {
  return cs_base64_decode(s, len, dst, NULL);
}