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
 int /*<<< orphan*/  CMD_BUFLEN ; 
 int kdb_nextline ; 
 int /*<<< orphan*/  kdb_printf (char const*) ; 
 char const* kdb_prompt_str ; 
 char* kdb_read (char*,size_t) ; 
 int /*<<< orphan*/  strscpy (char const*,char const*,int /*<<< orphan*/ ) ; 

char *kdb_getstr(char *buffer, size_t bufsize, const char *prompt)
{
	if (prompt && kdb_prompt_str != prompt)
		strscpy(kdb_prompt_str, prompt, CMD_BUFLEN);
	kdb_printf(kdb_prompt_str);
	kdb_nextline = 1;	/* Prompt and input resets line number */
	return kdb_read(buffer, bufsize);
}