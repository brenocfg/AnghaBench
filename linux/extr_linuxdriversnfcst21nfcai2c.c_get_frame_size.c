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
typedef  scalar_t__ u8 ;

/* Variables and functions */
 scalar_t__ ST21NFCA_SOF_EOF ; 

__attribute__((used)) static int get_frame_size(u8 *buf, int buflen)
{
	int len = 0;

	if (buf[len + 1] == ST21NFCA_SOF_EOF)
		return 0;

	for (len = 1; len < buflen && buf[len] != ST21NFCA_SOF_EOF; len++)
		;

	return len;
}