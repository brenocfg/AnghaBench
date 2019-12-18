#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {void* C; void* B; void* A; } ;
typedef  TYPE_1__ LINE ;

/* Variables and functions */
 int /*<<< orphan*/  DELIM ; 
 int /*<<< orphan*/  RDELIM_L ; 
 scalar_t__ isspace (unsigned char) ; 
 void* single_decode (char*,char**,char*,char const*) ; 

__attribute__((used)) static bool
line_decode(char *s, const char *str, LINE *line)
{
	/* s was already advanced over leading '{' */
	line->A = single_decode(s, &s, "line", str);
	if (*s++ != DELIM)
		return false;
	line->B = single_decode(s, &s, "line", str);
	if (*s++ != DELIM)
		return false;
	line->C = single_decode(s, &s, "line", str);
	if (*s++ != RDELIM_L)
		return false;
	while (isspace((unsigned char) *s))
		s++;
	if (*s != '\0')
		return false;
	return true;
}