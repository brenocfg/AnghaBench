#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {size_t bufsize; scalar_t__ buf; } ;

/* Variables and functions */
 scalar_t__ big_oops_buf ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,size_t) ; 
 TYPE_1__* psinfo ; 

__attribute__((used)) static size_t copy_kmsg_to_buffer(int hsize, size_t len)
{
	size_t total_len;
	size_t diff;

	total_len = hsize + len;

	if (total_len > psinfo->bufsize) {
		diff = total_len - psinfo->bufsize + hsize;
		memcpy(psinfo->buf, big_oops_buf, hsize);
		memcpy(psinfo->buf + hsize, big_oops_buf + diff,
					psinfo->bufsize - hsize);
		total_len = psinfo->bufsize;
	} else
		memcpy(psinfo->buf, big_oops_buf, total_len);

	return total_len;
}