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
 char toupper (unsigned char) ; 

__attribute__((used)) static void clean_line(char* oline, const char* line) {
	int cn = 0, n = 0;

	while (line[cn] != 0 && line[cn] != '\n' && line[cn] != ';') {
		if (line[cn] >= '!' && line[cn] <= '~') {
			char current_char = line[cn];
			
			/* Convert to upper case */
			if (current_char >= 'a' && current_char <= 'z')
				current_char = toupper ((unsigned char)current_char);
				
			/* Place in cleaned line */
			oline[n] = current_char;
			n++;
		}
		cn++;
	}
	oline[n] = 0;
}