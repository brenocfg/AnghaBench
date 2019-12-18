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

/* Variables and functions */
 int /*<<< orphan*/  send_string (char*) ; 
 size_t strcspn (char const*,char*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,size_t) ; 
 char tolower (unsigned char) ; 
 int /*<<< orphan*/  unicode_input_finish () ; 
 int /*<<< orphan*/  unicode_input_start () ; 

void send_unicode_hex_string(const char *str) {
    if (!str) {
        return;
    }

    while (*str) {
        // Find the next code point (token) in the string
        for (; *str == ' '; str++)
            ;
        size_t n = strcspn(str, " ");  // Length of the current token
        char   code_point[n + 1];
        strncpy(code_point, str, n);
        code_point[n] = '\0';  // Make sure it's null-terminated

        // Normalize the code point: make all hex digits lowercase
        for (char *p = code_point; *p; p++) {
            *p = tolower((unsigned char)*p);
        }

        // Send the code point as a Unicode input string
        unicode_input_start();
        send_string(code_point);
        unicode_input_finish();

        str += n;  // Move to the first ' ' (or '\0') after the current token
    }
}