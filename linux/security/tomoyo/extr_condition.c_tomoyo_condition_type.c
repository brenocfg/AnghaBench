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
typedef  size_t u8 ;

/* Variables and functions */
 size_t TOMOYO_MAX_CONDITION_KEYWORD ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * tomoyo_condition_keyword ; 

__attribute__((used)) static u8 tomoyo_condition_type(const char *word)
{
	u8 i;

	for (i = 0; i < TOMOYO_MAX_CONDITION_KEYWORD; i++) {
		if (!strcmp(word, tomoyo_condition_keyword[i]))
			break;
	}
	return i;
}