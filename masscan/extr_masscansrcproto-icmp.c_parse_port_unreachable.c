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

__attribute__((used)) static int
parse_port_unreachable(const unsigned char *px, unsigned length,
        unsigned *r_ip_me, unsigned *r_ip_them,
        unsigned *r_port_me, unsigned *r_port_them,
        unsigned *r_ip_proto)
{
    if (length < 24)
        return -1;
    *r_ip_me = px[12]<<24 | px[13]<<16 | px[14]<<8 | px[15];
    *r_ip_them = px[16]<<24 | px[17]<<16 | px[18]<<8 | px[19];
    *r_ip_proto = px[9]; /* TCP=6, UDP=17 */

    px += (px[0]&0xF)<<2;
    length -= (px[0]&0xF)<<2;

    if (length < 4)
        return -1;

    *r_port_me = px[0]<<8 | px[1];
    *r_port_them = px[2]<<8 | px[3];

    return 0;
}