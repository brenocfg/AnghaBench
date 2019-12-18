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
#define  PLPGSQL_NSTYPE_REC 129 
#define  PLPGSQL_NSTYPE_VAR 128 
 int /*<<< orphan*/ * list_make2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  makeString (char*) ; 
 void** plpgsql_Datums ; 
 scalar_t__ plpgsql_IdentifierLookup ; 
 int /*<<< orphan*/ * plpgsql_build_recfield (int /*<<< orphan*/ *,char*) ; 
 TYPE_2__* plpgsql_ns_lookup (int /*<<< orphan*/ ,int,char*,char*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  plpgsql_ns_top () ; 

bool
plpgsql_parse_dblword(char *word1, char *word2,
					  PLwdatum *wdatum, PLcword *cword)
{
	PLpgSQL_nsitem *ns;
	List	   *idents;
	int			nnames;

	idents = list_make2(makeString(word1),
						makeString(word2));

	/*
	 * We should do nothing in DECLARE sections.  In SQL expressions, we
	 * really only need to make sure that RECFIELD datums are created when
	 * needed.
	 */
	if (plpgsql_IdentifierLookup != IDENTIFIER_LOOKUP_DECLARE)
	{
		/*
		 * Do a lookup in the current namespace stack
		 */
		ns = plpgsql_ns_lookup(plpgsql_ns_top(), false,
							   word1, word2, NULL,
							   &nnames);
		if (ns != NULL)
		{
			switch (ns->itemtype)
			{
				case PLPGSQL_NSTYPE_VAR:
					/* Block-qualified reference to scalar variable. */
					wdatum->datum = plpgsql_Datums[ns->itemno];
					wdatum->ident = NULL;
					wdatum->quoted = false; /* not used */
					wdatum->idents = idents;
					return true;

				case PLPGSQL_NSTYPE_REC:
					if (nnames == 1)
					{
						/*
						 * First word is a record name, so second word could
						 * be a field in this record.  We build a RECFIELD
						 * datum whether it is or not --- any error will be
						 * detected later.
						 */
						PLpgSQL_rec *rec;
						PLpgSQL_recfield *new;

						rec = (PLpgSQL_rec *) (plpgsql_Datums[ns->itemno]);
						new = plpgsql_build_recfield(rec, word2);

						wdatum->datum = (PLpgSQL_datum *) new;
					}
					else
					{
						/* Block-qualified reference to record variable. */
						wdatum->datum = plpgsql_Datums[ns->itemno];
					}
					wdatum->ident = NULL;
					wdatum->quoted = false; /* not used */
					wdatum->idents = idents;
					return true;

				default:
					break;
			}
		}
	}

	/* Nothing found */
	cword->idents = idents;
	return false;
}