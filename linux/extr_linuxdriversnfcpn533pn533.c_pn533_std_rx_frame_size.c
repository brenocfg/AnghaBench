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
struct pn533_std_frame {int datalen; } ;
struct pn533_ext_frame {int /*<<< orphan*/  datalen; } ;

/* Variables and functions */
 int PN533_STD_FRAME_TAIL_LEN ; 
 scalar_t__ PN533_STD_IS_EXTENDED (struct pn533_std_frame*) ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int pn533_std_rx_frame_size(void *frame)
{
	struct pn533_std_frame *f = frame;

	/* check for Extended Information frame */
	if (PN533_STD_IS_EXTENDED(f)) {
		struct pn533_ext_frame *eif = frame;

		return sizeof(struct pn533_ext_frame)
			+ be16_to_cpu(eif->datalen) + PN533_STD_FRAME_TAIL_LEN;
	}

	return sizeof(struct pn533_std_frame) + f->datalen +
	       PN533_STD_FRAME_TAIL_LEN;
}