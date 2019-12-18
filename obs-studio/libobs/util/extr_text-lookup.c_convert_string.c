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
struct dstr {char* array; size_t capacity; size_t len; } ;

/* Variables and functions */
 char* bstrdup_n (char const*,size_t) ; 
 int /*<<< orphan*/  dstr_replace (struct dstr*,char*,char*) ; 

__attribute__((used)) static char *convert_string(const char *str, size_t len)
{
	struct dstr out;
	out.array = bstrdup_n(str, len);
	out.capacity = len + 1;
	out.len = len;

	dstr_replace(&out, "\\n", "\n");
	dstr_replace(&out, "\\t", "\t");
	dstr_replace(&out, "\\r", "\r");
	dstr_replace(&out, "\\\"", "\"");

	return out.array;
}