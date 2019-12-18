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
typedef  size_t u32 ;
struct btf {char* strings; } ;

/* Variables and functions */
 int KSYM_NAME_LEN ; 
 int /*<<< orphan*/  __btf_name_char_ok (char const,int,int) ; 

__attribute__((used)) static bool __btf_name_valid(const struct btf *btf, u32 offset, bool dot_ok)
{
	/* offset must be valid */
	const char *src = &btf->strings[offset];
	const char *src_limit;

	if (!__btf_name_char_ok(*src, true, dot_ok))
		return false;

	/* set a limit on identifier length */
	src_limit = src + KSYM_NAME_LEN;
	src++;
	while (*src && src < src_limit) {
		if (!__btf_name_char_ok(*src, false, dot_ok))
			return false;
		src++;
	}

	return !*src;
}