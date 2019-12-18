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
typedef  size_t utf8_size_t ;
typedef  int /*<<< orphan*/  utf8_char_t ;

/* Variables and functions */
 scalar_t__ _utf8_newline (int /*<<< orphan*/  const*) ; 
 size_t utf8_char_length (int /*<<< orphan*/  const*) ; 
 scalar_t__ utf8_char_whitespace (int /*<<< orphan*/  const*) ; 

utf8_size_t utf8_wrap_length(const utf8_char_t* data, utf8_size_t size)
{
    // Set split_at to size, so if a split point cna not be found, retuns the size passed in
    size_t char_length, char_count, split_at = size;

    for (char_count = 0; char_count <= size; ++char_count) {
        if (_utf8_newline(data)) {
            return char_count;
        } else if (utf8_char_whitespace(data)) {
            split_at = char_count;
        }

        char_length = utf8_char_length(data);
        data += char_length;
    }

    return split_at;
}