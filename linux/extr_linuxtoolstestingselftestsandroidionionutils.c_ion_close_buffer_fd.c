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
struct ion_buffer_info {scalar_t__ buffd; scalar_t__ ionfd; int /*<<< orphan*/  buflen; int /*<<< orphan*/  buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  close (scalar_t__) ; 
 int /*<<< orphan*/  munmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ion_close_buffer_fd(struct ion_buffer_info *ion_info)
{
	if (ion_info) {
		/* unmap the buffer properly in the end */
		munmap(ion_info->buffer, ion_info->buflen);
		/* close the buffer fd */
		if (ion_info->buffd > 0)
			close(ion_info->buffd);
		/* Finally, close the client fd */
		if (ion_info->ionfd > 0)
			close(ion_info->ionfd);
	}
}