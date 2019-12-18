#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
struct TYPE_24__ {scalar_t__ type; char* character; TYPE_1__* key; } ;
struct TYPE_23__ {int lsign; int pre_lsign_num; int post; int pre; int zero_end; scalar_t__ zero_start; int /*<<< orphan*/  flag; } ;
struct TYPE_22__ {int is_to_char; char* number; char* inout; char* last_relevant; int read_post; int read_dec; int out_pre_spaces; int sign; int sign_wrote; int num_count; char* number_p; char* inout_p; char* L_thousands_sep; char* L_currency_symbol; TYPE_3__* Num; scalar_t__ num_in; scalar_t__ num_curr; scalar_t__ read_pre; } ;
struct TYPE_21__ {int id; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_2__ NUMProc ;
typedef  TYPE_3__ NUMDesc ;
typedef  TYPE_4__ FormatNode ;

/* Variables and functions */
 int /*<<< orphan*/  AMOUNT_TEST (int) ; 
 int /*<<< orphan*/  DEBUG_elog_output ; 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ IS_BRACKET (TYPE_3__*) ; 
 scalar_t__ IS_DECIMAL (TYPE_3__*) ; 
 scalar_t__ IS_EEEE (TYPE_3__*) ; 
 scalar_t__ IS_FILLMODE (TYPE_3__*) ; 
 int IS_LSIGN (TYPE_3__*) ; 
 int IS_MINUS (TYPE_3__*) ; 
 scalar_t__ IS_PLUS (TYPE_3__*) ; 
 scalar_t__ IS_ROMAN (TYPE_3__*) ; 
 scalar_t__ IS_ZERO (TYPE_3__*) ; 
 int /*<<< orphan*/  MemSet (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ NODE_TYPE_ACTION ; 
 scalar_t__ NODE_TYPE_END ; 
#define  NUM_0 141 
#define  NUM_9 140 
#define  NUM_COMMA 139 
#define  NUM_D 138 
#define  NUM_DEC 137 
 int /*<<< orphan*/  NUM_F_BRACKET ; 
 int /*<<< orphan*/  NUM_F_FILLMODE ; 
 int /*<<< orphan*/  NUM_F_MINUS ; 
 int /*<<< orphan*/  NUM_F_PLUS ; 
 int /*<<< orphan*/  NUM_F_ROMAN ; 
#define  NUM_G 136 
#define  NUM_L 135 
 scalar_t__ NUM_LSIGN_POST ; 
 scalar_t__ NUM_LSIGN_PRE ; 
#define  NUM_MI 134 
#define  NUM_PL 133 
#define  NUM_RN 132 
#define  NUM_SG 131 
#define  NUM_TH 130 
 int /*<<< orphan*/  NUM_eat_non_data_chars (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  NUM_numpart_from_char (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  NUM_numpart_to_char (TYPE_2__*,int) ; 
 int /*<<< orphan*/  NUM_prepare_locale (TYPE_2__*) ; 
#define  NUM_rn 129 
#define  NUM_th 128 
 scalar_t__ OVERLOAD_TEST ; 
 int /*<<< orphan*/  TH_LOWER ; 
 int /*<<< orphan*/  TH_UPPER ; 
 char* asc_tolower_z (char*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 char* get_last_relevant_decnum (char*) ; 
 char* get_th (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 int /*<<< orphan*/  pg_mblen (char const*) ; 
 int pg_mbstrlen (char const*) ; 
 int /*<<< orphan*/  sprintf (char const*,char*,char*) ; 
 char* strcpy (char*,char const*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncmp (char*,char const*,int) ; 

__attribute__((used)) static char *
NUM_processor(FormatNode *node, NUMDesc *Num, char *inout,
			  char *number, int input_len, int to_char_out_pre_spaces,
			  int sign, bool is_to_char, Oid collid)
{
	FormatNode *n;
	NUMProc		_Np,
			   *Np = &_Np;
	const char *pattern;
	int			pattern_len;

	MemSet(Np, 0, sizeof(NUMProc));

	Np->Num = Num;
	Np->is_to_char = is_to_char;
	Np->number = number;
	Np->inout = inout;
	Np->last_relevant = NULL;
	Np->read_post = 0;
	Np->read_pre = 0;
	Np->read_dec = false;

	if (Np->Num->zero_start)
		--Np->Num->zero_start;

	if (IS_EEEE(Np->Num))
	{
		if (!Np->is_to_char)
			ereport(ERROR,
					(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
					 errmsg("\"EEEE\" not supported for input")));
		return strcpy(inout, number);
	}

	/*
	 * Roman correction
	 */
	if (IS_ROMAN(Np->Num))
	{
		if (!Np->is_to_char)
			ereport(ERROR,
					(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
					 errmsg("\"RN\" not supported for input")));

		Np->Num->lsign = Np->Num->pre_lsign_num = Np->Num->post =
			Np->Num->pre = Np->out_pre_spaces = Np->sign = 0;

		if (IS_FILLMODE(Np->Num))
		{
			Np->Num->flag = 0;
			Np->Num->flag |= NUM_F_FILLMODE;
		}
		else
			Np->Num->flag = 0;
		Np->Num->flag |= NUM_F_ROMAN;
	}

	/*
	 * Sign
	 */
	if (is_to_char)
	{
		Np->sign = sign;

		/* MI/PL/SG - write sign itself and not in number */
		if (IS_PLUS(Np->Num) || IS_MINUS(Np->Num))
		{
			if (IS_PLUS(Np->Num) && IS_MINUS(Np->Num) == false)
				Np->sign_wrote = false; /* need sign */
			else
				Np->sign_wrote = true;	/* needn't sign */
		}
		else
		{
			if (Np->sign != '-')
			{
				if (IS_BRACKET(Np->Num) && IS_FILLMODE(Np->Num))
					Np->Num->flag &= ~NUM_F_BRACKET;
				if (IS_MINUS(Np->Num))
					Np->Num->flag &= ~NUM_F_MINUS;
			}
			else if (Np->sign != '+' && IS_PLUS(Np->Num))
				Np->Num->flag &= ~NUM_F_PLUS;

			if (Np->sign == '+' && IS_FILLMODE(Np->Num) && IS_LSIGN(Np->Num) == false)
				Np->sign_wrote = true;	/* needn't sign */
			else
				Np->sign_wrote = false; /* need sign */

			if (Np->Num->lsign == NUM_LSIGN_PRE && Np->Num->pre == Np->Num->pre_lsign_num)
				Np->Num->lsign = NUM_LSIGN_POST;
		}
	}
	else
		Np->sign = false;

	/*
	 * Count
	 */
	Np->num_count = Np->Num->post + Np->Num->pre - 1;

	if (is_to_char)
	{
		Np->out_pre_spaces = to_char_out_pre_spaces;

		if (IS_FILLMODE(Np->Num) && IS_DECIMAL(Np->Num))
		{
			Np->last_relevant = get_last_relevant_decnum(Np->number);

			/*
			 * If any '0' specifiers are present, make sure we don't strip
			 * those digits.
			 */
			if (Np->last_relevant && Np->Num->zero_end > Np->out_pre_spaces)
			{
				char	   *last_zero;

				last_zero = Np->number + (Np->Num->zero_end - Np->out_pre_spaces);
				if (Np->last_relevant < last_zero)
					Np->last_relevant = last_zero;
			}
		}

		if (Np->sign_wrote == false && Np->out_pre_spaces == 0)
			++Np->num_count;
	}
	else
	{
		Np->out_pre_spaces = 0;
		*Np->number = ' ';		/* sign space */
		*(Np->number + 1) = '\0';
	}

	Np->num_in = 0;
	Np->num_curr = 0;

#ifdef DEBUG_TO_FROM_CHAR
	elog(DEBUG_elog_output,
		 "\n\tSIGN: '%c'\n\tNUM: '%s'\n\tPRE: %d\n\tPOST: %d\n\tNUM_COUNT: %d\n\tNUM_PRE: %d\n\tSIGN_WROTE: %s\n\tZERO: %s\n\tZERO_START: %d\n\tZERO_END: %d\n\tLAST_RELEVANT: %s\n\tBRACKET: %s\n\tPLUS: %s\n\tMINUS: %s\n\tFILLMODE: %s\n\tROMAN: %s\n\tEEEE: %s",
		 Np->sign,
		 Np->number,
		 Np->Num->pre,
		 Np->Num->post,
		 Np->num_count,
		 Np->out_pre_spaces,
		 Np->sign_wrote ? "Yes" : "No",
		 IS_ZERO(Np->Num) ? "Yes" : "No",
		 Np->Num->zero_start,
		 Np->Num->zero_end,
		 Np->last_relevant ? Np->last_relevant : "<not set>",
		 IS_BRACKET(Np->Num) ? "Yes" : "No",
		 IS_PLUS(Np->Num) ? "Yes" : "No",
		 IS_MINUS(Np->Num) ? "Yes" : "No",
		 IS_FILLMODE(Np->Num) ? "Yes" : "No",
		 IS_ROMAN(Np->Num) ? "Yes" : "No",
		 IS_EEEE(Np->Num) ? "Yes" : "No"
		);
#endif

	/*
	 * Locale
	 */
	NUM_prepare_locale(Np);

	/*
	 * Processor direct cycle
	 */
	if (Np->is_to_char)
		Np->number_p = Np->number;
	else
		Np->number_p = Np->number + 1;	/* first char is space for sign */

	for (n = node, Np->inout_p = Np->inout; n->type != NODE_TYPE_END; n++)
	{
		if (!Np->is_to_char)
		{
			/*
			 * Check at least one byte remains to be scanned.  (In actions
			 * below, must use AMOUNT_TEST if we want to read more bytes than
			 * that.)
			 */
			if (OVERLOAD_TEST)
				break;
		}

		/*
		 * Format pictures actions
		 */
		if (n->type == NODE_TYPE_ACTION)
		{
			/*
			 * Create/read digit/zero/blank/sign/special-case
			 *
			 * 'NUM_S' note: The locale sign is anchored to number and we
			 * read/write it when we work with first or last number
			 * (NUM_0/NUM_9).  This is why NUM_S is missing in switch().
			 *
			 * Notice the "Np->inout_p++" at the bottom of the loop.  This is
			 * why most of the actions advance inout_p one less than you might
			 * expect.  In cases where we don't want that increment to happen,
			 * a switch case ends with "continue" not "break".
			 */
			switch (n->key->id)
			{
				case NUM_9:
				case NUM_0:
				case NUM_DEC:
				case NUM_D:
					if (Np->is_to_char)
					{
						NUM_numpart_to_char(Np, n->key->id);
						continue;	/* for() */
					}
					else
					{
						NUM_numpart_from_char(Np, n->key->id, input_len);
						break;	/* switch() case: */
					}

				case NUM_COMMA:
					if (Np->is_to_char)
					{
						if (!Np->num_in)
						{
							if (IS_FILLMODE(Np->Num))
								continue;
							else
								*Np->inout_p = ' ';
						}
						else
							*Np->inout_p = ',';
					}
					else
					{
						if (!Np->num_in)
						{
							if (IS_FILLMODE(Np->Num))
								continue;
						}
						if (*Np->inout_p != ',')
							continue;
					}
					break;

				case NUM_G:
					pattern = Np->L_thousands_sep;
					pattern_len = strlen(pattern);
					if (Np->is_to_char)
					{
						if (!Np->num_in)
						{
							if (IS_FILLMODE(Np->Num))
								continue;
							else
							{
								/* just in case there are MB chars */
								pattern_len = pg_mbstrlen(pattern);
								memset(Np->inout_p, ' ', pattern_len);
								Np->inout_p += pattern_len - 1;
							}
						}
						else
						{
							strcpy(Np->inout_p, pattern);
							Np->inout_p += pattern_len - 1;
						}
					}
					else
					{
						if (!Np->num_in)
						{
							if (IS_FILLMODE(Np->Num))
								continue;
						}

						/*
						 * Because L_thousands_sep typically contains data
						 * characters (either '.' or ','), we can't use
						 * NUM_eat_non_data_chars here.  Instead skip only if
						 * the input matches L_thousands_sep.
						 */
						if (AMOUNT_TEST(pattern_len) &&
							strncmp(Np->inout_p, pattern, pattern_len) == 0)
							Np->inout_p += pattern_len - 1;
						else
							continue;
					}
					break;

				case NUM_L:
					pattern = Np->L_currency_symbol;
					if (Np->is_to_char)
					{
						strcpy(Np->inout_p, pattern);
						Np->inout_p += strlen(pattern) - 1;
					}
					else
					{
						NUM_eat_non_data_chars(Np, pg_mbstrlen(pattern), input_len);
						continue;
					}
					break;

				case NUM_RN:
					if (IS_FILLMODE(Np->Num))
					{
						strcpy(Np->inout_p, Np->number_p);
						Np->inout_p += strlen(Np->inout_p) - 1;
					}
					else
					{
						sprintf(Np->inout_p, "%15s", Np->number_p);
						Np->inout_p += strlen(Np->inout_p) - 1;
					}
					break;

				case NUM_rn:
					if (IS_FILLMODE(Np->Num))
					{
						strcpy(Np->inout_p, asc_tolower_z(Np->number_p));
						Np->inout_p += strlen(Np->inout_p) - 1;
					}
					else
					{
						sprintf(Np->inout_p, "%15s", asc_tolower_z(Np->number_p));
						Np->inout_p += strlen(Np->inout_p) - 1;
					}
					break;

				case NUM_th:
					if (IS_ROMAN(Np->Num) || *Np->number == '#' ||
						Np->sign == '-' || IS_DECIMAL(Np->Num))
						continue;

					if (Np->is_to_char)
					{
						strcpy(Np->inout_p, get_th(Np->number, TH_LOWER));
						Np->inout_p += 1;
					}
					else
					{
						/* All variants of 'th' occupy 2 characters */
						NUM_eat_non_data_chars(Np, 2, input_len);
						continue;
					}
					break;

				case NUM_TH:
					if (IS_ROMAN(Np->Num) || *Np->number == '#' ||
						Np->sign == '-' || IS_DECIMAL(Np->Num))
						continue;

					if (Np->is_to_char)
					{
						strcpy(Np->inout_p, get_th(Np->number, TH_UPPER));
						Np->inout_p += 1;
					}
					else
					{
						/* All variants of 'TH' occupy 2 characters */
						NUM_eat_non_data_chars(Np, 2, input_len);
						continue;
					}
					break;

				case NUM_MI:
					if (Np->is_to_char)
					{
						if (Np->sign == '-')
							*Np->inout_p = '-';
						else if (IS_FILLMODE(Np->Num))
							continue;
						else
							*Np->inout_p = ' ';
					}
					else
					{
						if (*Np->inout_p == '-')
							*Np->number = '-';
						else
						{
							NUM_eat_non_data_chars(Np, 1, input_len);
							continue;
						}
					}
					break;

				case NUM_PL:
					if (Np->is_to_char)
					{
						if (Np->sign == '+')
							*Np->inout_p = '+';
						else if (IS_FILLMODE(Np->Num))
							continue;
						else
							*Np->inout_p = ' ';
					}
					else
					{
						if (*Np->inout_p == '+')
							*Np->number = '+';
						else
						{
							NUM_eat_non_data_chars(Np, 1, input_len);
							continue;
						}
					}
					break;

				case NUM_SG:
					if (Np->is_to_char)
						*Np->inout_p = Np->sign;
					else
					{
						if (*Np->inout_p == '-')
							*Np->number = '-';
						else if (*Np->inout_p == '+')
							*Np->number = '+';
						else
						{
							NUM_eat_non_data_chars(Np, 1, input_len);
							continue;
						}
					}
					break;

				default:
					continue;
					break;
			}
		}
		else
		{
			/*
			 * In TO_CHAR, non-pattern characters in the format are copied to
			 * the output.  In TO_NUMBER, we skip one input character for each
			 * non-pattern format character, whether or not it matches the
			 * format character.
			 */
			if (Np->is_to_char)
			{
				strcpy(Np->inout_p, n->character);
				Np->inout_p += strlen(Np->inout_p);
			}
			else
			{
				Np->inout_p += pg_mblen(Np->inout_p);
			}
			continue;
		}
		Np->inout_p++;
	}

	if (Np->is_to_char)
	{
		*Np->inout_p = '\0';
		return Np->inout;
	}
	else
	{
		if (*(Np->number_p - 1) == '.')
			*(Np->number_p - 1) = '\0';
		else
			*Np->number_p = '\0';

		/*
		 * Correction - precision of dec. number
		 */
		Np->Num->post = Np->read_post;

#ifdef DEBUG_TO_FROM_CHAR
		elog(DEBUG_elog_output, "TO_NUMBER (number): '%s'", Np->number);
#endif
		return Np->number;
	}
}