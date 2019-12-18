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
 int CHAR_BIT ; 
 char* EMPTY ; 
 int /*<<< orphan*/  base_yydebug ; 
 int base_yylineno ; 
 char* input_filename ; 
 char* mm_alloc (int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int strlen (char*) ; 

char *
hashline_number(void)
{
	/* do not print line numbers if we are in debug mode */
	if (input_filename
#ifdef YYDEBUG
		&& !base_yydebug
#endif
		)
	{
		/* "* 2" here is for escaping '\' and '"' below */
		char	   *line = mm_alloc(strlen("\n#line %d \"%s\"\n") + sizeof(int) * CHAR_BIT * 10 / 3 + strlen(input_filename) * 2);
		char	   *src,
				   *dest;

		sprintf(line, "\n#line %d \"", base_yylineno);
		src = input_filename;
		dest = line + strlen(line);
		while (*src)
		{
			if (*src == '\\' || *src == '"')
				*dest++ = '\\';
			*dest++ = *src++;
		}
		*dest = '\0';
		strcat(dest, "\"\n");

		return line;
	}

	return EMPTY;
}