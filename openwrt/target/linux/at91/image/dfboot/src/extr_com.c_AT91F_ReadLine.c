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
 int /*<<< orphan*/  AT91C_CB_SIZE ; 
 char* erase_seq ; 
 char getc () ; 
 int /*<<< orphan*/  printf (char const* const) ; 
 int /*<<< orphan*/  putc (char) ; 
 int /*<<< orphan*/  puts (char*) ; 
 int strlen (char const* const) ; 

int AT91F_ReadLine (const char *const prompt, char *console_buffer)
{
	char *p = console_buffer;
	int	n = 0;					/* buffer index		*/
	int	plen = strlen (prompt);	/* prompt length	*/
	int	col;					/* output column cnt	*/
	char	c;

	/* print prompt */
	if (prompt)
		printf(prompt);
	col = plen;

	for (;;) {
		c = getc();

		switch (c) {
			case '\r':				/* Enter		*/
			case '\n':
				*p = '\0';
				puts ("\n");
				return (p - console_buffer);

			case 0x03:				/* ^C - break	*/
				console_buffer[0] = '\0';	/* discard input */
				return (-1);

			case 0x08:				/* ^H  - backspace	*/
			case 0x7F:				/* DEL - backspace	*/
				if (n) {
					--p;
					printf(erase_seq);
					col--;
					n--;
					}
				continue;

			default:
			/*
			 * Must be a normal character then
			 */
			if (n < (AT91C_CB_SIZE -2)) 
			{
				++col;		/* echo input		*/
				putc(c);
				*p++ = c;
				++n;
			} 
			else 
			{			/* Buffer full		*/
				putc('\a');
			}
		}
	}
}