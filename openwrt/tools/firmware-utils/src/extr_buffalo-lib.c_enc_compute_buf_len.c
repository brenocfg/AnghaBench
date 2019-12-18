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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 unsigned long enc_compute_header_len (char*,char*) ; 

unsigned long enc_compute_buf_len(char *product, char *version,
				  unsigned long datalen)
{
	unsigned long ret;

	ret = enc_compute_header_len(product, version);
	ret += datalen + sizeof(uint32_t);
	ret += (4 - ret % 4);

	return ret;
}