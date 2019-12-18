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
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 char* pp_xmalloc (int) ; 
 int strbuf_idx ; 
 int /*<<< orphan*/  strbuffer ; 

__attribute__((used)) static char *get_string(void)
{
	char *str = pp_xmalloc(strbuf_idx + 1);
	if(!str)
		return NULL;
	memcpy(str, strbuffer, strbuf_idx);
	str[strbuf_idx] = '\0';
#ifdef DEBUG
	strbuf_idx = 0;
#endif
	return str;
}