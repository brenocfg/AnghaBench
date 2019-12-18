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

/* Variables and functions */
#define  CAPFILE_BIGENDIAN 129 
#define  CAPFILE_LITTLEENDIAN 128 

__attribute__((used)) static unsigned PCAP32(unsigned byte_order, const unsigned char *buf)
{
    switch (byte_order) {
    case CAPFILE_BIGENDIAN: return buf[0]<<24 | buf[1]<<16 | buf[2] << 8 | buf[3];
    case CAPFILE_LITTLEENDIAN: return buf[3]<<24 | buf[2]<<16 | buf[1] << 8 | buf[0];
    default: return (unsigned)0xa3a3;
    }
}