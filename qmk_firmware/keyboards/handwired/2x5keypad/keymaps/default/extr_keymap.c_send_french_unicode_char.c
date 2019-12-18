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
typedef  int uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  send_unicode_hex_string (char*) ; 

void send_french_unicode_char(uint8_t count, char *once, char *twice)
{
    if (count <= 1)
	send_unicode_hex_string(once);
    else
	send_unicode_hex_string(twice); 
}