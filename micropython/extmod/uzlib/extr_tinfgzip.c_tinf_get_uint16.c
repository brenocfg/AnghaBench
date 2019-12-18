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
typedef  unsigned int uint16_t ;
typedef  int /*<<< orphan*/  TINF_DATA ;

/* Variables and functions */
 int uzlib_get_byte (int /*<<< orphan*/ *) ; 

uint16_t tinf_get_uint16(TINF_DATA *d)
{
    unsigned int v = uzlib_get_byte(d);
    v = (uzlib_get_byte(d) << 8) | v;
    return v;
}