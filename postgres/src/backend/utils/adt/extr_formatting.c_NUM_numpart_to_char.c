#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int zero_start; scalar_t__ lsign; } ;
struct TYPE_10__ {int sign_wrote; int num_curr; char* number_p; int num_in; int out_pre_spaces; char* last_relevant; char sign; char* inout_p; int num_count; int /*<<< orphan*/  L_positive_sign; int /*<<< orphan*/  L_negative_sign; TYPE_3__* Num; int /*<<< orphan*/  decimal; int /*<<< orphan*/  inout; } ;
typedef  TYPE_1__ NUMProc ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_elog_output ; 
 scalar_t__ IS_BRACKET (TYPE_3__*) ; 
 scalar_t__ IS_DECIMAL (TYPE_3__*) ; 
 scalar_t__ IS_FILLMODE (TYPE_3__*) ; 
 scalar_t__ IS_LSIGN (TYPE_3__*) ; 
 int IS_PREDEC_SPACE (TYPE_1__*) ; 
 scalar_t__ IS_ROMAN (TYPE_3__*) ; 
 scalar_t__ IS_ZERO (TYPE_3__*) ; 
 int NUM_0 ; 
 int NUM_9 ; 
 int NUM_D ; 
 int NUM_DEC ; 
 scalar_t__ NUM_LSIGN_POST ; 
 scalar_t__ NUM_LSIGN_PRE ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static void
NUM_numpart_to_char(NUMProc *Np, int id)
{
	int			end;

	if (IS_ROMAN(Np->Num))
		return;

	/* Note: in this elog() output not set '\0' in 'inout' */

#ifdef DEBUG_TO_FROM_CHAR

	/*
	 * Np->num_curr is number of current item in format-picture, it is not
	 * current position in inout!
	 */
	elog(DEBUG_elog_output,
		 "SIGN_WROTE: %d, CURRENT: %d, NUMBER_P: \"%s\", INOUT: \"%s\"",
		 Np->sign_wrote,
		 Np->num_curr,
		 Np->number_p,
		 Np->inout);
#endif
	Np->num_in = false;

	/*
	 * Write sign if real number will write to output Note: IS_PREDEC_SPACE()
	 * handle "9.9" --> " .1"
	 */
	if (Np->sign_wrote == false &&
		(Np->num_curr >= Np->out_pre_spaces || (IS_ZERO(Np->Num) && Np->Num->zero_start == Np->num_curr)) &&
		(IS_PREDEC_SPACE(Np) == false || (Np->last_relevant && *Np->last_relevant == '.')))
	{
		if (IS_LSIGN(Np->Num))
		{
			if (Np->Num->lsign == NUM_LSIGN_PRE)
			{
				if (Np->sign == '-')
					strcpy(Np->inout_p, Np->L_negative_sign);
				else
					strcpy(Np->inout_p, Np->L_positive_sign);
				Np->inout_p += strlen(Np->inout_p);
				Np->sign_wrote = true;
			}
		}
		else if (IS_BRACKET(Np->Num))
		{
			*Np->inout_p = Np->sign == '+' ? ' ' : '<';
			++Np->inout_p;
			Np->sign_wrote = true;
		}
		else if (Np->sign == '+')
		{
			if (!IS_FILLMODE(Np->Num))
			{
				*Np->inout_p = ' '; /* Write + */
				++Np->inout_p;
			}
			Np->sign_wrote = true;
		}
		else if (Np->sign == '-')
		{						/* Write - */
			*Np->inout_p = '-';
			++Np->inout_p;
			Np->sign_wrote = true;
		}
	}


	/*
	 * digits / FM / Zero / Dec. point
	 */
	if (id == NUM_9 || id == NUM_0 || id == NUM_D || id == NUM_DEC)
	{
		if (Np->num_curr < Np->out_pre_spaces &&
			(Np->Num->zero_start > Np->num_curr || !IS_ZERO(Np->Num)))
		{
			/*
			 * Write blank space
			 */
			if (!IS_FILLMODE(Np->Num))
			{
				*Np->inout_p = ' '; /* Write ' ' */
				++Np->inout_p;
			}
		}
		else if (IS_ZERO(Np->Num) &&
				 Np->num_curr < Np->out_pre_spaces &&
				 Np->Num->zero_start <= Np->num_curr)
		{
			/*
			 * Write ZERO
			 */
			*Np->inout_p = '0'; /* Write '0' */
			++Np->inout_p;
			Np->num_in = true;
		}
		else
		{
			/*
			 * Write Decimal point
			 */
			if (*Np->number_p == '.')
			{
				if (!Np->last_relevant || *Np->last_relevant != '.')
				{
					strcpy(Np->inout_p, Np->decimal);	/* Write DEC/D */
					Np->inout_p += strlen(Np->inout_p);
				}

				/*
				 * Ora 'n' -- FM9.9 --> 'n.'
				 */
				else if (IS_FILLMODE(Np->Num) &&
						 Np->last_relevant && *Np->last_relevant == '.')
				{
					strcpy(Np->inout_p, Np->decimal);	/* Write DEC/D */
					Np->inout_p += strlen(Np->inout_p);
				}
			}
			else
			{
				/*
				 * Write Digits
				 */
				if (Np->last_relevant && Np->number_p > Np->last_relevant &&
					id != NUM_0)
					;

				/*
				 * '0.1' -- 9.9 --> '  .1'
				 */
				else if (IS_PREDEC_SPACE(Np))
				{
					if (!IS_FILLMODE(Np->Num))
					{
						*Np->inout_p = ' ';
						++Np->inout_p;
					}

					/*
					 * '0' -- FM9.9 --> '0.'
					 */
					else if (Np->last_relevant && *Np->last_relevant == '.')
					{
						*Np->inout_p = '0';
						++Np->inout_p;
					}
				}
				else
				{
					*Np->inout_p = *Np->number_p;	/* Write DIGIT */
					++Np->inout_p;
					Np->num_in = true;
				}
			}
			/* do no exceed string length */
			if (*Np->number_p)
				++Np->number_p;
		}

		end = Np->num_count + (Np->out_pre_spaces ? 1 : 0) + (IS_DECIMAL(Np->Num) ? 1 : 0);

		if (Np->last_relevant && Np->last_relevant == Np->number_p)
			end = Np->num_curr;

		if (Np->num_curr + 1 == end)
		{
			if (Np->sign_wrote == true && IS_BRACKET(Np->Num))
			{
				*Np->inout_p = Np->sign == '+' ? ' ' : '>';
				++Np->inout_p;
			}
			else if (IS_LSIGN(Np->Num) && Np->Num->lsign == NUM_LSIGN_POST)
			{
				if (Np->sign == '-')
					strcpy(Np->inout_p, Np->L_negative_sign);
				else
					strcpy(Np->inout_p, Np->L_positive_sign);
				Np->inout_p += strlen(Np->inout_p);
			}
		}
	}

	++Np->num_curr;
}