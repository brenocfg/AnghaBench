#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16 ;
struct TYPE_4__ {char* lexeme; int flags; int /*<<< orphan*/  nvariant; } ;
typedef  TYPE_1__ TSLexeme ;

/* Variables and functions */
 int MAX_NORM ; 
 scalar_t__ palloc (int) ; 

__attribute__((used)) static void
addNorm(TSLexeme **lres, TSLexeme **lcur, char *word, int flags, uint16 NVariant)
{
	if (*lres == NULL)
		*lcur = *lres = (TSLexeme *) palloc(MAX_NORM * sizeof(TSLexeme));

	if (*lcur - *lres < MAX_NORM - 1)
	{
		(*lcur)->lexeme = word;
		(*lcur)->flags = flags;
		(*lcur)->nvariant = NVariant;
		(*lcur)++;
		(*lcur)->lexeme = NULL;
	}
}