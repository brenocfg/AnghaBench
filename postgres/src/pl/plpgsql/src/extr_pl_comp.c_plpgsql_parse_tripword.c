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
struct TYPE_9__ {int /*<<< orphan*/ * idents; } ;
struct TYPE_8__ {int itemtype; size_t itemno; } ;
struct TYPE_7__ {int quoted; int /*<<< orphan*/ * idents; int /*<<< orphan*/ * ident; int /*<<< orphan*/ * datum; } ;
typedef  TYPE_1__ PLwdatum ;
typedef  int /*<<< orphan*/  PLpgSQL_recfield ;
typedef  int /*<<< orphan*/  PLpgSQL_rec ;
typedef  TYPE_2__ PLpgSQL_nsitem ;
typedef  int /*<<< orphan*/  PLpgSQL_datum ;
typedef  TYPE_3__ PLcword ;
typedef  int /*<<< orphan*/  List ;

/* Variables and functions */
 scalar_t__ IDENTIFIER_LOOKUP_DECLARE ; 
#define  PLPGSQL_NSTYPE_REC 128 
 int /*<<< orphan*/ * list_make3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  makeString (char*) ; 
 scalar_t__* plpgsql_Datums ; 
 scalar_t__ plpgsql_IdentifierLookup ; 
 int /*<<< orphan*/ * plpgsql_build_recfield (int /*<<< orphan*/ *,char*) ; 
 TYPE_2__* plpgsql_ns_lookup (int /*<<< orphan*/ ,int,char*,char*,char*,int*) ; 
 int /*<<< orphan*/  plpgsql_ns_top () ; 

bool
plpgsql_parse_tripword(char *word1, char *word2, char *word3,
					   PLwdatum *wdatum, PLcword *cword)
{
	PLpgSQL_nsitem *ns;
	List	   *idents;
	int			nnames;

	idents = list_make3(makeString(word1),
						makeString(word2),
						makeString(word3));

	/*
	 * We should do nothing in DECLARE sections.  In SQL expressions, we
	 * really only need to make sure that RECFIELD datums are created when
	 * needed.
	 */
	if (plpgsql_IdentifierLookup != IDENTIFIER_LOOKUP_DECLARE)
	{
		/*
		 * Do a lookup in the current namespace stack. Must find a qualified
		 * reference, else ignore.
		 */
		ns = plpgsql_ns_lookup(plpgsql_ns_top(), false,
							   word1, word2, word3,
							   &nnames);
		if (ns != NULL && nnames == 2)
		{
			switch (ns->itemtype)
			{
				case PLPGSQL_NSTYPE_REC:
					{
						/*
						 * words 1/2 are a record name, so third word could be
						 * a field in this record.
						 */
						PLpgSQL_rec *rec;
						PLpgSQL_recfield *new;

						rec = (PLpgSQL_rec *) (plpgsql_Datums[ns->itemno]);
						new = plpgsql_build_recfield(rec, word3);

						wdatum->datum = (PLpgSQL_datum *) new;
						wdatum->ident = NULL;
						wdatum->quoted = false; /* not used */
						wdatum->idents = idents;
						return true;
					}

				default:
					break;
			}
		}
	}

	/* Nothing found */
	cword->idents = idents;
	return false;
}