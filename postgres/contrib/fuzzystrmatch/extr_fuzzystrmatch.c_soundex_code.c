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
 char* soundex_table ; 
 char toupper (unsigned char) ; 

__attribute__((used)) static char
soundex_code(char letter)
{
	letter = toupper((unsigned char) letter);
	/* Defend against non-ASCII letters */
	if (letter >= 'A' && letter <= 'Z')
		return soundex_table[letter - 'A'];
	return letter;
}