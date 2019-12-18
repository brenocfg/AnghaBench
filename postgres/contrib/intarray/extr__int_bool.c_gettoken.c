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
typedef  int /*<<< orphan*/  nnn ;
typedef  scalar_t__ int32 ;
struct TYPE_3__ {int state; char* buf; int /*<<< orphan*/  count; } ;
typedef  TYPE_1__ WORKSTATE ;

/* Variables and functions */
 scalar_t__ CLOSE ; 
 scalar_t__ END ; 
 scalar_t__ ERR ; 
 scalar_t__ OPEN ; 
 scalar_t__ OPR ; 
 scalar_t__ VAL ; 
#define  WAITENDOPERAND 130 
#define  WAITOPERAND 129 
#define  WAITOPERATOR 128 
 int /*<<< orphan*/  errno ; 
 long strtol (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int32
gettoken(WORKSTATE *state, int32 *val)
{
	char		nnn[16];
	int			innn;

	*val = 0;					/* default result */

	innn = 0;
	while (1)
	{
		if (innn >= sizeof(nnn))
			return ERR;			/* buffer overrun => syntax error */
		switch (state->state)
		{
			case WAITOPERAND:
				innn = 0;
				if ((*(state->buf) >= '0' && *(state->buf) <= '9') ||
					*(state->buf) == '-')
				{
					state->state = WAITENDOPERAND;
					nnn[innn++] = *(state->buf);
				}
				else if (*(state->buf) == '!')
				{
					(state->buf)++;
					*val = (int32) '!';
					return OPR;
				}
				else if (*(state->buf) == '(')
				{
					state->count++;
					(state->buf)++;
					return OPEN;
				}
				else if (*(state->buf) != ' ')
					return ERR;
				break;
			case WAITENDOPERAND:
				if (*(state->buf) >= '0' && *(state->buf) <= '9')
				{
					nnn[innn++] = *(state->buf);
				}
				else
				{
					long		lval;

					nnn[innn] = '\0';
					errno = 0;
					lval = strtol(nnn, NULL, 0);
					*val = (int32) lval;
					if (errno != 0 || (long) *val != lval)
						return ERR;
					state->state = WAITOPERATOR;
					return (state->count && *(state->buf) == '\0')
						? ERR : VAL;
				}
				break;
			case WAITOPERATOR:
				if (*(state->buf) == '&' || *(state->buf) == '|')
				{
					state->state = WAITOPERAND;
					*val = (int32) *(state->buf);
					(state->buf)++;
					return OPR;
				}
				else if (*(state->buf) == ')')
				{
					(state->buf)++;
					state->count--;
					return (state->count < 0) ? ERR : CLOSE;
				}
				else if (*(state->buf) == '\0')
					return (state->count) ? ERR : END;
				else if (*(state->buf) != ' ')
					return ERR;
				break;
			default:
				return ERR;
				break;
		}
		(state->buf)++;
	}
}