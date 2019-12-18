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
typedef  int /*<<< orphan*/  text ;
typedef  int /*<<< orphan*/  TmToChar ;
struct TYPE_3__ {char* format; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  char FormatNode ;
typedef  TYPE_1__ DCHCacheEntry ;

/* Variables and functions */
 int DCH_CACHE_SIZE ; 
 int /*<<< orphan*/  DCH_FLAG ; 
 int DCH_MAX_ITEM_SIZ ; 
 TYPE_1__* DCH_cache_fetch (char*,int) ; 
 int /*<<< orphan*/  DCH_index ; 
 int /*<<< orphan*/  DCH_keywords ; 
 int /*<<< orphan*/  DCH_suff ; 
 int /*<<< orphan*/  DCH_to_char (char*,int,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cstring_to_text (char*) ; 
 char* palloc (int) ; 
 int /*<<< orphan*/  parse_format (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 int strlen (char*) ; 
 char* text_to_cstring (int /*<<< orphan*/ *) ; 

__attribute__((used)) static text *
datetime_to_char_body(TmToChar *tmtc, text *fmt, bool is_interval, Oid collid)
{
	FormatNode *format;
	char	   *fmt_str,
			   *result;
	bool		incache;
	int			fmt_len;
	text	   *res;

	/*
	 * Convert fmt to C string
	 */
	fmt_str = text_to_cstring(fmt);
	fmt_len = strlen(fmt_str);

	/*
	 * Allocate workspace for result as C string
	 */
	result = palloc((fmt_len * DCH_MAX_ITEM_SIZ) + 1);
	*result = '\0';

	if (fmt_len > DCH_CACHE_SIZE)
	{
		/*
		 * Allocate new memory if format picture is bigger than static cache
		 * and do not use cache (call parser always)
		 */
		incache = false;

		format = (FormatNode *) palloc((fmt_len + 1) * sizeof(FormatNode));

		parse_format(format, fmt_str, DCH_keywords,
					 DCH_suff, DCH_index, DCH_FLAG, NULL);
	}
	else
	{
		/*
		 * Use cache buffers
		 */
		DCHCacheEntry *ent = DCH_cache_fetch(fmt_str, false);

		incache = true;
		format = ent->format;
	}

	/* The real work is here */
	DCH_to_char(format, is_interval, tmtc, result, collid);

	if (!incache)
		pfree(format);

	pfree(fmt_str);

	/* convert C-string result to TEXT format */
	res = cstring_to_text(result);

	pfree(result);
	return res;
}