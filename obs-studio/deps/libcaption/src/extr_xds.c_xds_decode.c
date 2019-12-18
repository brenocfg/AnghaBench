#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int state; int class_code; int type; int checksum; int size; int* content; } ;
typedef  TYPE_1__ xds_t ;
typedef  int uint16_t ;

/* Variables and functions */
 int LIBCAPTION_ERROR ; 
 int LIBCAPTION_OK ; 
 int LIBCAPTION_READY ; 
 int /*<<< orphan*/  xds_init (TYPE_1__*) ; 

int xds_decode(xds_t* xds, uint16_t cc)
{
    switch (xds->state) {
    default:
    case 0:
        xds_init(xds);
        xds->class_code = (cc & 0x0F00) >> 8;
        xds->type = (cc & 0x000F);
        xds->state = 1;
        return LIBCAPTION_OK;

    case 1:
        if (0x8F00 == (cc & 0xFF00)) {
            xds->checksum = (cc & 0x007F);
            xds->state = 0;
            return LIBCAPTION_READY;
        }

        if (xds->size < 32) {
            xds->content[xds->size + 0] = (cc & 0x7F00) >> 8;
            xds->content[xds->size + 1] = (cc & 0x007F);
            xds->size += 2;
            return LIBCAPTION_OK;
        }
    }

    xds->state = 0;
    return LIBCAPTION_ERROR;
}