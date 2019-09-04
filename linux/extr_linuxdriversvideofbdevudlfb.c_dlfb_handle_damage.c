#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct urb {char* transfer_buffer; int transfer_buffer_length; } ;
struct dlfb_data {int /*<<< orphan*/  cpu_kcycles_used; int /*<<< orphan*/  bytes_rendered; int /*<<< orphan*/  bytes_identical; int /*<<< orphan*/  bytes_sent; TYPE_3__* info; int /*<<< orphan*/  usb_active; } ;
typedef  int cycles_t ;
struct TYPE_5__ {int line_length; scalar_t__ smem_start; } ;
struct TYPE_4__ {int xres; int yres; } ;
struct TYPE_6__ {TYPE_2__ fix; TYPE_1__ var; } ;

/* Variables and functions */
 int BPP ; 
 int DL_ALIGN_DOWN (int,int) ; 
 int DL_ALIGN_UP (int,int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  atomic_add (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 struct urb* dlfb_get_urb (struct dlfb_data*) ; 
 scalar_t__ dlfb_render_hline (struct dlfb_data*,struct urb**,char*,char**,int const,int,int*,int*) ; 
 int dlfb_submit_urb (struct dlfb_data*,struct urb*,int) ; 
 int /*<<< orphan*/  dlfb_urb_completion (struct urb*) ; 
 int get_cycles () ; 

__attribute__((used)) static int dlfb_handle_damage(struct dlfb_data *dlfb, int x, int y,
	       int width, int height, char *data)
{
	int i, ret;
	char *cmd;
	cycles_t start_cycles, end_cycles;
	int bytes_sent = 0;
	int bytes_identical = 0;
	struct urb *urb;
	int aligned_x;

	start_cycles = get_cycles();

	aligned_x = DL_ALIGN_DOWN(x, sizeof(unsigned long));
	width = DL_ALIGN_UP(width + (x-aligned_x), sizeof(unsigned long));
	x = aligned_x;

	if ((width <= 0) ||
	    (x + width > dlfb->info->var.xres) ||
	    (y + height > dlfb->info->var.yres))
		return -EINVAL;

	if (!atomic_read(&dlfb->usb_active))
		return 0;

	urb = dlfb_get_urb(dlfb);
	if (!urb)
		return 0;
	cmd = urb->transfer_buffer;

	for (i = y; i < y + height ; i++) {
		const int line_offset = dlfb->info->fix.line_length * i;
		const int byte_offset = line_offset + (x * BPP);

		if (dlfb_render_hline(dlfb, &urb,
				      (char *) dlfb->info->fix.smem_start,
				      &cmd, byte_offset, width * BPP,
				      &bytes_identical, &bytes_sent))
			goto error;
	}

	if (cmd > (char *) urb->transfer_buffer) {
		int len;
		if (cmd < (char *) urb->transfer_buffer + urb->transfer_buffer_length)
			*cmd++ = 0xAF;
		/* Send partial buffer remaining before exiting */
		len = cmd - (char *) urb->transfer_buffer;
		ret = dlfb_submit_urb(dlfb, urb, len);
		bytes_sent += len;
	} else
		dlfb_urb_completion(urb);

error:
	atomic_add(bytes_sent, &dlfb->bytes_sent);
	atomic_add(bytes_identical, &dlfb->bytes_identical);
	atomic_add(width*height*2, &dlfb->bytes_rendered);
	end_cycles = get_cycles();
	atomic_add(((unsigned int) ((end_cycles - start_cycles)
		    >> 10)), /* Kcycles */
		   &dlfb->cpu_kcycles_used);

	return 0;
}