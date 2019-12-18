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
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 char* VARDATA_ANY (int /*<<< orphan*/ ) ; 
 int VARSIZE_ANY_EXHDR (int /*<<< orphan*/ ) ; 
 int tsCompareString (char*,int,char*,int,int) ; 

__attribute__((used)) static int
compare_text_lexemes(const void *va, const void *vb)
{
	Datum		a = *((const Datum *) va);
	Datum		b = *((const Datum *) vb);
	char	   *alex = VARDATA_ANY(a);
	int			alex_len = VARSIZE_ANY_EXHDR(a);
	char	   *blex = VARDATA_ANY(b);
	int			blex_len = VARSIZE_ANY_EXHDR(b);

	return tsCompareString(alex, alex_len, blex, blex_len, false);
}