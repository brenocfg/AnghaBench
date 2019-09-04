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
typedef  char utf8_char_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 size_t utf8_char_length (char const*) ; 

size_t utf8_char_copy(utf8_char_t* dst, const utf8_char_t* src)
{
    size_t bytes = utf8_char_length(src);

    if (bytes && dst) {
        memcpy(dst, src, bytes);
        dst[bytes] = '\0';
    }

    return bytes;
}