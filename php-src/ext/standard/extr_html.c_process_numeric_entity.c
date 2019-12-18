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
typedef  scalar_t__ zend_long ;

/* Variables and functions */
 int FAILURE ; 
 int SUCCESS ; 
 scalar_t__ ZEND_STRTOL (char const*,char**,int) ; 
 scalar_t__ Z_L (int) ; 
 int /*<<< orphan*/  isdigit (char const) ; 
 int /*<<< orphan*/  isxdigit (char const) ; 

__attribute__((used)) static inline int process_numeric_entity(const char **buf, unsigned *code_point)
{
	zend_long code_l;
	int hexadecimal = (**buf == 'x' || **buf == 'X'); /* TODO: XML apparently disallows "X" */
	char *endptr;

	if (hexadecimal && (**buf != '\0'))
		(*buf)++;

	/* strtol allows whitespace and other stuff in the beginning
		* we're not interested */
	if ((hexadecimal && !isxdigit(**buf)) ||
			(!hexadecimal && !isdigit(**buf))) {
		return FAILURE;
	}

	code_l = ZEND_STRTOL(*buf, &endptr, hexadecimal ? 16 : 10);
	/* we're guaranteed there were valid digits, so *endptr > buf */
	*buf = endptr;

	if (**buf != ';')
		return FAILURE;

	/* many more are invalid, but that depends on whether it's HTML
	 * (and which version) or XML. */
	if (code_l > Z_L(0x10FFFF))
		return FAILURE;

	if (code_point != NULL)
		*code_point = (unsigned)code_l;

	return SUCCESS;
}