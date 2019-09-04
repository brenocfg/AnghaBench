#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {unsigned char* dest; int checksum_type; unsigned int checksum; } ;
typedef  TYPE_1__ TINF_DATA ;

/* Variables and functions */
#define  TINF_CHKSUM_ADLER 129 
#define  TINF_CHKSUM_CRC 128 
 int TINF_CHKSUM_ERROR ; 
 int TINF_DONE ; 
 unsigned int tinf_get_be_uint32 (TYPE_1__*) ; 
 unsigned int tinf_get_le_uint32 (TYPE_1__*) ; 
 unsigned int uzlib_adler32 (unsigned char*,int,unsigned int) ; 
 unsigned int uzlib_crc32 (unsigned char*,int,unsigned int) ; 
 int uzlib_uncompress (TYPE_1__*) ; 

int uzlib_uncompress_chksum(TINF_DATA *d)
{
    int res;
    unsigned char *data = d->dest;

    res = uzlib_uncompress(d);

    if (res < 0) return res;

    switch (d->checksum_type) {

    case TINF_CHKSUM_ADLER:
        d->checksum = uzlib_adler32(data, d->dest - data, d->checksum);
        break;

    case TINF_CHKSUM_CRC:
        d->checksum = uzlib_crc32(data, d->dest - data, d->checksum);
        break;
    }

    if (res == TINF_DONE) {
        unsigned int val;

        switch (d->checksum_type) {

        case TINF_CHKSUM_ADLER:
            val = tinf_get_be_uint32(d);
            if (d->checksum != val) {
                return TINF_CHKSUM_ERROR;
            }
            break;

        case TINF_CHKSUM_CRC:
            val = tinf_get_le_uint32(d);
            if (~d->checksum != val) {
                return TINF_CHKSUM_ERROR;
            }
            // Uncompressed size. TODO: Check
            val = tinf_get_le_uint32(d);
            break;
        }
    }

    return res;
}