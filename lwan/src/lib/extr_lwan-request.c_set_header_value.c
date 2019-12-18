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
struct lwan_value {char* value; size_t len; } ;

/* Variables and functions */
 scalar_t__ LIKELY (int) ; 
 scalar_t__ STR2_INT (char,char) ; 
 scalar_t__ string_as_uint16 (char*) ; 

__attribute__((used)) __attribute__((noinline)) static void set_header_value(
    struct lwan_value *header, char *end, char *p, size_t header_len)
{
    p += header_len;

    if (LIKELY(string_as_uint16(p) == STR2_INT(':', ' '))) {
        *end = '\0';
        char *value = p + sizeof(": ") - 1;

        header->value = value;
        header->len = (size_t)(end - value);
    }
}