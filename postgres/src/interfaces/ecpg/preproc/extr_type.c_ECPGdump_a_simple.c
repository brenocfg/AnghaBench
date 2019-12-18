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
typedef  enum ECPGttype { ____Placeholder_ECPGttype } ECPGttype ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int CHAR_BIT ; 
 int ECPGt_NO_INDICATOR ; 
#define  ECPGt_bytea 138 
#define  ECPGt_char 137 
#define  ECPGt_char_variable 136 
#define  ECPGt_const 135 
#define  ECPGt_date 134 
 int ECPGt_descriptor ; 
#define  ECPGt_interval 133 
#define  ECPGt_numeric 132 
 int ECPGt_sqlda ; 
#define  ECPGt_string 131 
#define  ECPGt_timestamp 130 
#define  ECPGt_unsigned_char 129 
#define  ECPGt_varchar 128 
 scalar_t__ atoi (char*) ; 
 char* ecpg_type_name (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* get_type (int) ; 
 scalar_t__ mm_alloc (scalar_t__) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static void
ECPGdump_a_simple(FILE *o, const char *name, enum ECPGttype type,
				  char *varcharsize,
				  char *arrsize,
				  const char *size,
				  const char *prefix,
				  int counter)
{
	if (type == ECPGt_NO_INDICATOR)
		fprintf(o, "\n\tECPGt_NO_INDICATOR, NULL , 0L, 0L, 0L, ");
	else if (type == ECPGt_descriptor)
		/* remember that name here already contains quotes (if needed) */
		fprintf(o, "\n\tECPGt_descriptor, %s, 1L, 1L, 1L, ", name);
	else if (type == ECPGt_sqlda)
		fprintf(o, "\n\tECPGt_sqlda, &%s, 0L, 0L, 0L, ", name);
	else
	{
		char	   *variable = (char *) mm_alloc(strlen(name) + ((prefix == NULL) ? 0 : strlen(prefix)) + 4);
		char	   *offset = (char *) mm_alloc(strlen(name) + strlen("sizeof(struct varchar_)") + 1 + strlen(varcharsize) + sizeof(int) * CHAR_BIT * 10 / 3);
		char	   *struct_name;

		switch (type)
		{
				/*
				 * we have to use the & operator except for arrays and
				 * pointers
				 */

			case ECPGt_varchar:
			case ECPGt_bytea:

				/*
				 * we have to use the pointer except for arrays with given
				 * bounds
				 */
				if (((atoi(arrsize) > 0) ||
					 (atoi(arrsize) == 0 && strcmp(arrsize, "0") != 0)) &&
					size == NULL)
					sprintf(variable, "(%s%s)", prefix ? prefix : "", name);
				else
					sprintf(variable, "&(%s%s)", prefix ? prefix : "", name);

				/*
				 * If we created a varchar structure automatically, counter is
				 * greater than 0.
				 */
				if (type == ECPGt_varchar)
					struct_name = "struct varchar";
				else
					struct_name = "struct bytea";

				if (counter)
					sprintf(offset, "sizeof(%s_%d)", struct_name, counter);
				else
					sprintf(offset, "sizeof(%s)", struct_name);
				break;
			case ECPGt_char:
			case ECPGt_unsigned_char:
			case ECPGt_char_variable:
			case ECPGt_string:
				{
					char	   *sizeof_name = "char";

					/*
					 * we have to use the pointer except for arrays with given
					 * bounds, ecpglib will distinguish between * and []
					 */
					if ((atoi(varcharsize) > 1 ||
						 (atoi(arrsize) > 0) ||
						 (atoi(varcharsize) == 0 && strcmp(varcharsize, "0") != 0) ||
						 (atoi(arrsize) == 0 && strcmp(arrsize, "0") != 0))
						&& size == NULL)
					{
						sprintf(variable, "(%s%s)", prefix ? prefix : "", name);
						if ((type == ECPGt_char || type == ECPGt_unsigned_char) &&
							strcmp(varcharsize, "0") == 0)
						{
							/*
							 * If this is an array of char *, the offset would
							 * be sizeof(char *) and not sizeof(char).
							 */
							sizeof_name = "char *";
						}
					}
					else
						sprintf(variable, "&(%s%s)", prefix ? prefix : "", name);

					sprintf(offset, "(%s)*sizeof(%s)", strcmp(varcharsize, "0") == 0 ? "1" : varcharsize, sizeof_name);
					break;
				}
			case ECPGt_numeric:

				/*
				 * we have to use a pointer here
				 */
				sprintf(variable, "&(%s%s)", prefix ? prefix : "", name);
				sprintf(offset, "sizeof(numeric)");
				break;
			case ECPGt_interval:

				/*
				 * we have to use a pointer here
				 */
				sprintf(variable, "&(%s%s)", prefix ? prefix : "", name);
				sprintf(offset, "sizeof(interval)");
				break;
			case ECPGt_date:

				/*
				 * we have to use a pointer and translate the variable type
				 */
				sprintf(variable, "&(%s%s)", prefix ? prefix : "", name);
				sprintf(offset, "sizeof(date)");
				break;
			case ECPGt_timestamp:

				/*
				 * we have to use a pointer and translate the variable type
				 */
				sprintf(variable, "&(%s%s)", prefix ? prefix : "", name);
				sprintf(offset, "sizeof(timestamp)");
				break;
			case ECPGt_const:

				/*
				 * just dump the const as string
				 */
				sprintf(variable, "\"%s\"", name);
				sprintf(offset, "strlen(\"%s\")", name);
				break;
			default:

				/*
				 * we have to use the pointer except for arrays with given
				 * bounds
				 */
				if (((atoi(arrsize) > 0) ||
					 (atoi(arrsize) == 0 && strcmp(arrsize, "0") != 0)) &&
					size == NULL)
					sprintf(variable, "(%s%s)", prefix ? prefix : "", name);
				else
					sprintf(variable, "&(%s%s)", prefix ? prefix : "", name);

				sprintf(offset, "sizeof(%s)", ecpg_type_name(type));
				break;
		}

		/*
		 * Array size would be -1 for addresses of members within structure,
		 * when pointer to structure is being dumped.
		 */
		if (atoi(arrsize) < 0 && !size)
			strcpy(arrsize, "1");

		/*
		 * If size i.e. the size of structure of which this variable is part
		 * of, that gives the offset to the next element, if required
		 */
		if (size == NULL || strlen(size) == 0)
			fprintf(o, "\n\t%s,%s,(long)%s,(long)%s,%s, ", get_type(type), variable, varcharsize, arrsize, offset);
		else
			fprintf(o, "\n\t%s,%s,(long)%s,(long)%s,%s, ", get_type(type), variable, varcharsize, arrsize, size);

		free(variable);
		free(offset);
	}
}