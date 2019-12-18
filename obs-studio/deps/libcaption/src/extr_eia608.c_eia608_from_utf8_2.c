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
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  _eia608_from_utf8 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  eia608_from_basicna (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

uint16_t eia608_from_utf8_2(const utf8_char_t* c1, const utf8_char_t* c2)
{
    uint16_t cc1 = _eia608_from_utf8(c1);
    uint16_t cc2 = _eia608_from_utf8(c2);
    return eia608_from_basicna(cc1, cc2);
}