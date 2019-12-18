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
 unsigned char* strchr (unsigned char const*,char) ; 
 int strlen (unsigned char const*) ; 
 int /*<<< orphan*/  tomoyo_correct_word2 (unsigned char const*,int) ; 

bool tomoyo_domain_def(const unsigned char *buffer)
{
	const unsigned char *cp;
	int len;

	if (*buffer != '<')
		return false;
	cp = strchr(buffer, ' ');
	if (!cp)
		len = strlen(buffer);
	else
		len = cp - buffer;
	if (buffer[len - 1] != '>' ||
	    !tomoyo_correct_word2(buffer + 1, len - 2))
		return false;
	return true;
}