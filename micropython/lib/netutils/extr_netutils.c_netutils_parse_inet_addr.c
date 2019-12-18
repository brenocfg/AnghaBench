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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  netutils_endian_t ;
typedef  int /*<<< orphan*/  mp_uint_t ;
typedef  int /*<<< orphan*/  mp_obj_t ;

/* Variables and functions */
 int /*<<< orphan*/  mp_obj_get_array_fixed_n (int /*<<< orphan*/ ,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  mp_obj_get_int (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netutils_parse_ipv4_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

mp_uint_t netutils_parse_inet_addr(mp_obj_t addr_in, uint8_t *out_ip, netutils_endian_t endian) {
    mp_obj_t *addr_items;
    mp_obj_get_array_fixed_n(addr_in, 2, &addr_items);
    netutils_parse_ipv4_addr(addr_items[0], out_ip, endian);
    return mp_obj_get_int(addr_items[1]);
}