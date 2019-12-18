#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int itemtype; size_t itemno; } ;
struct TYPE_8__ {char* ident; int quoted; int /*<<< orphan*/  idents; int /*<<< orphan*/  datum; } ;
struct TYPE_7__ {char* ident; int quoted; } ;
typedef  TYPE_1__ PLword ;
typedef  TYPE_2__ PLwdatum ;
typedef  TYPE_3__ PLpgSQL_nsitem ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ IDENTIFIER_LOOKUP_NORMAL ; 
 int /*<<< orphan*/  NIL ; 
#define  PLPGSQL_NSTYPE_REC 129 
#define  PLPGSQL_NSTYPE_VAR 128 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/ * plpgsql_Datums ; 
 scalar_t__ plpgsql_IdentifierLookup ; 
 TYPE_3__* plpgsql_ns_lookup (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  plpgsql_ns_top () ; 

bool
plpgsql_parse_word(char *word1, const char *yytxt, bool lookup,
				   PLwdatum *wdatum, PLword *word)
{
	PLpgSQL_nsitem *ns;

	/*
	 * We should not lookup variables in DECLARE sections.  In SQL
	 * expressions, there's no need to do so either --- lookup will happen
	 * when the expression is compiled.
	 */
	if (lookup && plpgsql_IdentifierLookup == IDENTIFIER_LOOKUP_NORMAL)
	{
		/*
		 * Do a lookup in the current namespace stack
		 */
		ns = plpgsql_ns_lookup(plpgsql_ns_top(), false,
							   word1, NULL, NULL,
							   NULL);

		if (ns != NULL)
		{
			switch (ns->itemtype)
			{
				case PLPGSQL_NSTYPE_VAR:
				case PLPGSQL_NSTYPE_REC:
					wdatum->datum = plpgsql_Datums[ns->itemno];
					wdatum->ident = word1;
					wdatum->quoted = (yytxt[0] == '"');
					wdatum->idents = NIL;
					return true;

				default:
					/* plpgsql_ns_lookup should never return anything else */
					elog(ERROR, "unrecognized plpgsql itemtype: %d",
						 ns->itemtype);
			}
		}
	}

	/*
	 * Nothing found - up to now it's a word without any special meaning for
	 * us.
	 */
	word->ident = word1;
	word->quoted = (yytxt[0] == '"');
	return false;
}