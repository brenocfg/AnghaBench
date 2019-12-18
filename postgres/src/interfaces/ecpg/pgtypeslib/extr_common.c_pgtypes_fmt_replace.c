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
union un_fmt_comb {char* str_val; char char_val; double double_val; double int64_val; double uint_val; } ;

/* Variables and functions */
 int ENOMEM ; 
 char* INT64_FORMAT ; 
 int PGTYPES_FMT_NUM_MAX_DIGITS ; 
#define  PGTYPES_TYPE_CHAR 138 
#define  PGTYPES_TYPE_DOUBLE_NF 137 
#define  PGTYPES_TYPE_INT64 136 
#define  PGTYPES_TYPE_NOTHING 135 
#define  PGTYPES_TYPE_STRING_CONSTANT 134 
#define  PGTYPES_TYPE_STRING_MALLOCED 133 
#define  PGTYPES_TYPE_UINT 132 
#define  PGTYPES_TYPE_UINT_2_LS 131 
#define  PGTYPES_TYPE_UINT_2_LZ 130 
#define  PGTYPES_TYPE_UINT_3_LZ 129 
#define  PGTYPES_TYPE_UINT_4_LZ 128 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 char* pgtypes_alloc (int) ; 
 int snprintf (char*,int,char*,double) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 

int
pgtypes_fmt_replace(union un_fmt_comb replace_val, int replace_type, char **output, int *pstr_len)
{
	/*
	 * general purpose variable, set to 0 in order to fix compiler warning
	 */
	int			i = 0;

	switch (replace_type)
	{
		case PGTYPES_TYPE_NOTHING:
			break;
		case PGTYPES_TYPE_STRING_CONSTANT:
		case PGTYPES_TYPE_STRING_MALLOCED:
			i = strlen(replace_val.str_val);
			if (i + 1 <= *pstr_len)
			{
				/* include trailing terminator in what we copy */
				memcpy(*output, replace_val.str_val, i + 1);
				*pstr_len -= i;
				*output += i;
				if (replace_type == PGTYPES_TYPE_STRING_MALLOCED)
					free(replace_val.str_val);
				return 0;
			}
			else
				return -1;
			break;
		case PGTYPES_TYPE_CHAR:
			if (*pstr_len >= 2)
			{
				(*output)[0] = replace_val.char_val;
				(*output)[1] = '\0';
				(*pstr_len)--;
				(*output)++;
				return 0;
			}
			else
				return -1;
			break;
		case PGTYPES_TYPE_DOUBLE_NF:
		case PGTYPES_TYPE_INT64:
		case PGTYPES_TYPE_UINT:
		case PGTYPES_TYPE_UINT_2_LZ:
		case PGTYPES_TYPE_UINT_2_LS:
		case PGTYPES_TYPE_UINT_3_LZ:
		case PGTYPES_TYPE_UINT_4_LZ:
			{
				char	   *t = pgtypes_alloc(PGTYPES_FMT_NUM_MAX_DIGITS);

				if (!t)
					return ENOMEM;
				switch (replace_type)
				{
					case PGTYPES_TYPE_DOUBLE_NF:
						i = snprintf(t, PGTYPES_FMT_NUM_MAX_DIGITS,
									 "%0.0g", replace_val.double_val);
						break;
					case PGTYPES_TYPE_INT64:
						i = snprintf(t, PGTYPES_FMT_NUM_MAX_DIGITS,
									 INT64_FORMAT, replace_val.int64_val);
						break;
					case PGTYPES_TYPE_UINT:
						i = snprintf(t, PGTYPES_FMT_NUM_MAX_DIGITS,
									 "%u", replace_val.uint_val);
						break;
					case PGTYPES_TYPE_UINT_2_LZ:
						i = snprintf(t, PGTYPES_FMT_NUM_MAX_DIGITS,
									 "%02u", replace_val.uint_val);
						break;
					case PGTYPES_TYPE_UINT_2_LS:
						i = snprintf(t, PGTYPES_FMT_NUM_MAX_DIGITS,
									 "%2u", replace_val.uint_val);
						break;
					case PGTYPES_TYPE_UINT_3_LZ:
						i = snprintf(t, PGTYPES_FMT_NUM_MAX_DIGITS,
									 "%03u", replace_val.uint_val);
						break;
					case PGTYPES_TYPE_UINT_4_LZ:
						i = snprintf(t, PGTYPES_FMT_NUM_MAX_DIGITS,
									 "%04u", replace_val.uint_val);
						break;
				}

				if (i < 0 || i >= PGTYPES_FMT_NUM_MAX_DIGITS)
				{
					free(t);
					return -1;
				}
				i = strlen(t);
				*pstr_len -= i;

				/*
				 * if *pstr_len == 0, we don't have enough space for the
				 * terminator and the conversion fails
				 */
				if (*pstr_len <= 0)
				{
					free(t);
					return -1;
				}
				strcpy(*output, t);
				*output += i;
				free(t);
			}
			break;
		default:
			break;
	}
	return 0;
}