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
typedef  int /*<<< orphan*/  utf8_char_t ;
typedef  int uint16_t ;

/* Variables and functions */
 int _eia608_from_utf8 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  eia608_is_basicna (int) ; 
 int eia608_parity (int) ; 

uint16_t eia608_from_utf8_1(const utf8_char_t* c, int chan)
{
    uint16_t cc_data = _eia608_from_utf8(c);

    if (0 == cc_data) {
        return cc_data;
    }

    if (chan && !eia608_is_basicna(cc_data)) {
        cc_data |= 0x0800;
    }

    return eia608_parity(cc_data);
}