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
typedef  int uint32_t ;
struct serializer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (char*) ; 
 char* bmalloc (int) ; 
 int /*<<< orphan*/  read_data (struct serializer*,char*,int) ; 
 int /*<<< orphan*/  read_var (struct serializer*,int) ; 

__attribute__((used)) static bool read_str(struct serializer *s, char **p_str)
{
	uint32_t size;
	char *str;

	if (!read_var(s, size))
		return false;

	str = bmalloc(size + 1);
	if (size && !read_data(s, str, size)) {
		bfree(str);
		return false;
	}

	str[size] = 0;
	*p_str = str;
	return true;
}