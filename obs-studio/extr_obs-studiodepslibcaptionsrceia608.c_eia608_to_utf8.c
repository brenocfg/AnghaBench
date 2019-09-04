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
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 scalar_t__ eia608_to_index (int /*<<< orphan*/ ,int*,int*,int*) ; 
 int /*<<< orphan*/  utf8_char_copy (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  utf8_from_index (int) ; 

int eia608_to_utf8(uint16_t c, int* chan, char* str1, char* str2)
{
    int c1, c2;
    int size = (int)eia608_to_index(c, chan, &c1, &c2);
    utf8_char_copy(str1, utf8_from_index(c1));
    utf8_char_copy(str2, utf8_from_index(c2));
    return size;
}