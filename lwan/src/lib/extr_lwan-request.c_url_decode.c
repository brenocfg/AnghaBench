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
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ UNLIKELY (int) ; 
 int decode_hex_digit (char) ; 

__attribute__((used)) static ssize_t url_decode(char *str)
{
    if (UNLIKELY(!str))
        return -EINVAL;

    char *ch, *decoded;
    for (decoded = ch = str; *ch; ch++) {
        if (*ch == '%') {
            char tmp =
                (char)(decode_hex_digit(ch[1]) << 4 | decode_hex_digit(ch[2]));

            if (UNLIKELY(!tmp))
                return -EINVAL;

            *decoded++ = tmp;
            ch += 2;
        } else if (*ch == '+') {
            *decoded++ = ' ';
        } else {
            *decoded++ = *ch;
        }
    }

    *decoded = '\0';
    return (ssize_t)(decoded - str);
}