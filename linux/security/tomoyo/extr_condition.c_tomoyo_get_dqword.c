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
struct tomoyo_path_info {int dummy; } ;

/* Variables and functions */
 int strlen (char*) ; 
 int /*<<< orphan*/  tomoyo_correct_word (char*) ; 
 struct tomoyo_path_info const* tomoyo_get_name (char*) ; 

__attribute__((used)) static const struct tomoyo_path_info *tomoyo_get_dqword(char *start)
{
	char *cp = start + strlen(start) - 1;

	if (cp == start || *start++ != '"' || *cp != '"')
		return NULL;
	*cp = '\0';
	if (*start && !tomoyo_correct_word(start))
		return NULL;
	return tomoyo_get_name(start);
}