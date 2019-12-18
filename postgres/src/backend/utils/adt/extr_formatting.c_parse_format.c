#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
struct TYPE_11__ {scalar_t__ len; } ;
struct TYPE_10__ {int suffix; char* character; void* type; TYPE_7__* key; } ;
struct TYPE_9__ {int id; scalar_t__ len; } ;
typedef  int /*<<< orphan*/  NUMDesc ;
typedef  int /*<<< orphan*/  KeyWord ;
typedef  TYPE_1__ KeySuffix ;
typedef  TYPE_2__ FormatNode ;

/* Variables and functions */
 int DCH_FLAG ; 
 int /*<<< orphan*/  DEBUG_elog_output ; 
 int /*<<< orphan*/  ERRCODE_INVALID_DATETIME_FORMAT ; 
 int /*<<< orphan*/  ERROR ; 
 void* NODE_TYPE_ACTION ; 
 void* NODE_TYPE_CHAR ; 
 void* NODE_TYPE_END ; 
 void* NODE_TYPE_SEPARATOR ; 
 void* NODE_TYPE_SPACE ; 
 int /*<<< orphan*/  NUMDesc_prepare (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int NUM_FLAG ; 
 int STD_FLAG ; 
 int /*<<< orphan*/  SUFFTYPE_POSTFIX ; 
 int /*<<< orphan*/  SUFFTYPE_PREFIX ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 TYPE_7__* index_seq_search (char const*,int /*<<< orphan*/  const*,int const*) ; 
 scalar_t__ is_separator_char (char const*) ; 
 scalar_t__ isspace (unsigned char) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int pg_mblen (char const*) ; 
 int /*<<< orphan*/  pnstrdup (char const*,int) ; 
 int /*<<< orphan*/ * strchr (char*,char const) ; 
 TYPE_1__* suff_search (char const*,TYPE_1__ const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
parse_format(FormatNode *node, const char *str, const KeyWord *kw,
			 const KeySuffix *suf, const int *index, uint32 flags, NUMDesc *Num)
{
	FormatNode *n;

#ifdef DEBUG_TO_FROM_CHAR
	elog(DEBUG_elog_output, "to_char/number(): run parser");
#endif

	n = node;

	while (*str)
	{
		int			suffix = 0;
		const KeySuffix *s;

		/*
		 * Prefix
		 */
		if ((flags & DCH_FLAG) &&
			(s = suff_search(str, suf, SUFFTYPE_PREFIX)) != NULL)
		{
			suffix |= s->id;
			if (s->len)
				str += s->len;
		}

		/*
		 * Keyword
		 */
		if (*str && (n->key = index_seq_search(str, kw, index)) != NULL)
		{
			n->type = NODE_TYPE_ACTION;
			n->suffix = suffix;
			if (n->key->len)
				str += n->key->len;

			/*
			 * NUM version: Prepare global NUMDesc struct
			 */
			if (flags & NUM_FLAG)
				NUMDesc_prepare(Num, n);

			/*
			 * Postfix
			 */
			if ((flags & DCH_FLAG) && *str &&
				(s = suff_search(str, suf, SUFFTYPE_POSTFIX)) != NULL)
			{
				n->suffix |= s->id;
				if (s->len)
					str += s->len;
			}

			n++;
		}
		else if (*str)
		{
			int			chlen;

			if (flags & STD_FLAG)
			{
				/*
				 * Standard mode, allow only following separators: "-./,':; "
				 */
				if (strchr("-./,':; ", *str) == NULL)
					ereport(ERROR,
							(errcode(ERRCODE_INVALID_DATETIME_FORMAT),
							 errmsg("invalid datetime format separator: \"%s\"",
									pnstrdup(str, pg_mblen(str)))));

				if (*str == ' ')
					n->type = NODE_TYPE_SPACE;
				else
					n->type = NODE_TYPE_SEPARATOR;

				n->character[0] = *str;
				n->character[1] = '\0';
				n->key = NULL;
				n->suffix = 0;
				n++;
				str++;
			}
			else if (*str == '"')
			{
				/*
				 * Process double-quoted literal string, if any
				 */
				str++;
				while (*str)
				{
					if (*str == '"')
					{
						str++;
						break;
					}
					/* backslash quotes the next character, if any */
					if (*str == '\\' && *(str + 1))
						str++;
					chlen = pg_mblen(str);
					n->type = NODE_TYPE_CHAR;
					memcpy(n->character, str, chlen);
					n->character[chlen] = '\0';
					n->key = NULL;
					n->suffix = 0;
					n++;
					str += chlen;
				}
			}
			else
			{
				/*
				 * Outside double-quoted strings, backslash is only special if
				 * it immediately precedes a double quote.
				 */
				if (*str == '\\' && *(str + 1) == '"')
					str++;
				chlen = pg_mblen(str);

				if ((flags & DCH_FLAG) && is_separator_char(str))
					n->type = NODE_TYPE_SEPARATOR;
				else if (isspace((unsigned char) *str))
					n->type = NODE_TYPE_SPACE;
				else
					n->type = NODE_TYPE_CHAR;

				memcpy(n->character, str, chlen);
				n->character[chlen] = '\0';
				n->key = NULL;
				n->suffix = 0;
				n++;
				str += chlen;
			}
		}
	}

	n->type = NODE_TYPE_END;
	n->suffix = 0;
}