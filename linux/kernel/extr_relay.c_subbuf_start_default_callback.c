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
struct rchan_buf {int dummy; } ;

/* Variables and functions */
 scalar_t__ relay_buf_full (struct rchan_buf*) ; 

__attribute__((used)) static int subbuf_start_default_callback (struct rchan_buf *buf,
					  void *subbuf,
					  void *prev_subbuf,
					  size_t prev_padding)
{
	if (relay_buf_full(buf))
		return 0;

	return 1;
}