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
typedef  scalar_t__ utf8_size_t ;
typedef  int /*<<< orphan*/  utf8_char_t ;

/* Variables and functions */
 scalar_t__ utf8_char_count (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 size_t utf8_char_length (int /*<<< orphan*/  const*) ; 

size_t utf8_string_length(const utf8_char_t* data, utf8_size_t size)
{
    size_t char_length, byts = 0;

    if (0 == size) {
        size = utf8_char_count(data, 0);
    }

    for (; 0 < size; --size) {
        if (0 == (char_length = utf8_char_length(data))) {
            break;
        }

        data += char_length;
        byts += char_length;
    }

    return byts;
}