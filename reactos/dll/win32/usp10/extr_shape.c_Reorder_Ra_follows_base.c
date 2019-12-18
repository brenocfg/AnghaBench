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
typedef  int /*<<< orphan*/  lexical_function ;
typedef  int /*<<< orphan*/  WORD ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_3__ {scalar_t__ ralf; size_t start; int base; } ;
typedef  TYPE_1__ IndicSyllable ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,int) ; 

__attribute__((used)) static void Reorder_Ra_follows_base(WCHAR *pwChar, IndicSyllable *s, lexical_function lexical)
{
    if (s->ralf >= 0)
    {
        int j;
        WORD Ra = pwChar[s->start];
        WORD H = pwChar[s->start+1];

        TRACE("Doing reorder of Ra to %i\n",s->base);
        for (j = s->start; j < s->base-1; j++)
            pwChar[j] = pwChar[j+2];
        pwChar[s->base-1] = Ra;
        pwChar[s->base] = H;

        s->ralf = s->base-1;
        s->base -= 2;
    }
}