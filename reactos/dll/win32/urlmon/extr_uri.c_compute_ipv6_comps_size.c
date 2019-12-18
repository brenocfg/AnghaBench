#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int components_size; int h16_count; int elision_size; scalar_t__ elision; scalar_t__ ipv4; } ;
typedef  TYPE_1__ ipv6_address ;

/* Variables and functions */

__attribute__((used)) static void compute_ipv6_comps_size(ipv6_address *address) {
    address->components_size = address->h16_count * 2;

    if(address->ipv4)
        /* IPv4 address is 4 bytes. */
        address->components_size += 4;

    if(address->elision) {
        /* An elision can be anywhere from 2 bytes up to 16 bytes.
         * Its size depends on the size of the h16 and IPv4 components.
         */
        address->elision_size = 16 - address->components_size;
        if(address->elision_size < 2)
            address->elision_size = 2;
    } else
        address->elision_size = 0;
}