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
struct buf {int size; scalar_t__ start; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ HOST_TO_BE16 (unsigned short) ; 
 scalar_t__ force_be ; 

__attribute__((used)) static unsigned short fwcsum (struct buf *buf) {
    int i;
    unsigned short ret = 0;

    for (i = 0; i < buf->size / 2; i++) {
	if (force_be == FALSE)
	    ret -= ((unsigned short *) buf->start)[i];
	else
	    ret -= HOST_TO_BE16(((unsigned short *) buf->start)[i]);
    }
    
    return ret;
}