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

__attribute__((used)) static unsigned
pg_base64_enc_len(const char *src, unsigned srclen)
{
	/* 3 bytes will be converted to 4, linefeed after 76 chars */
	return (srclen + 2) * 4 / 3 + srclen / (76 * 3 / 4);
}