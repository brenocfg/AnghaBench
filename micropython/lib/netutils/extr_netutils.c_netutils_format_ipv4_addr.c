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
typedef  int uint8_t ;
typedef  scalar_t__ netutils_endian_t ;
typedef  int /*<<< orphan*/  mp_uint_t ;
typedef  int /*<<< orphan*/  mp_obj_t ;

/* Variables and functions */
 scalar_t__ NETUTILS_LITTLE ; 
 int /*<<< orphan*/  mp_obj_new_str (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int,int,int) ; 

mp_obj_t netutils_format_ipv4_addr(uint8_t *ip, netutils_endian_t endian) {
    char ip_str[16];
    mp_uint_t ip_len;
    if (endian == NETUTILS_LITTLE) {
        ip_len = snprintf(ip_str, 16, "%u.%u.%u.%u", ip[3], ip[2], ip[1], ip[0]);
    } else {
        ip_len = snprintf(ip_str, 16, "%u.%u.%u.%u", ip[0], ip[1], ip[2], ip[3]);
    }
    return mp_obj_new_str(ip_str, ip_len);
}