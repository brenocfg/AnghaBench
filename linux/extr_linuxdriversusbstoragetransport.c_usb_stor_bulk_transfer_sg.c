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
struct us_data {int dummy; } ;
struct scatterlist {int dummy; } ;

/* Variables and functions */
 int usb_stor_bulk_transfer_buf (struct us_data*,unsigned int,void*,unsigned int,unsigned int*) ; 
 int usb_stor_bulk_transfer_sglist (struct us_data*,unsigned int,struct scatterlist*,int,unsigned int,unsigned int*) ; 

int usb_stor_bulk_transfer_sg(struct us_data* us, unsigned int pipe,
		void *buf, unsigned int length_left, int use_sg, int *residual)
{
	int result;
	unsigned int partial;

	/* are we scatter-gathering? */
	if (use_sg) {
		/* use the usb core scatter-gather primitives */
		result = usb_stor_bulk_transfer_sglist(us, pipe,
				(struct scatterlist *) buf, use_sg,
				length_left, &partial);
		length_left -= partial;
	} else {
		/* no scatter-gather, just make the request */
		result = usb_stor_bulk_transfer_buf(us, pipe, buf, 
				length_left, &partial);
		length_left -= partial;
	}

	/* store the residual and return the error code */
	if (residual)
		*residual = length_left;
	return result;
}