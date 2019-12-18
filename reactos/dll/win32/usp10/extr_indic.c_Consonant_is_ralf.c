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
typedef  scalar_t__ (* lexical_function ) (int /*<<< orphan*/  const) ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_3__ {size_t start; size_t end; } ;
typedef  int /*<<< orphan*/  ScriptCache ;
typedef  int /*<<< orphan*/  SCRIPT_ANALYSIS ;
typedef  TYPE_1__ IndicSyllable ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int BOOL ;

/* Variables and functions */
 int FALSE ; 
 scalar_t__ SHAPE_does_GSUB_feature_apply_to_chars (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,int,char*) ; 
 scalar_t__ lex_Halant ; 
 scalar_t__ lex_Ra ; 

__attribute__((used)) static BOOL Consonant_is_ralf(HDC hdc, SCRIPT_ANALYSIS *psa, ScriptCache *psc,
        const WCHAR *pwChar, const IndicSyllable *s, lexical_function lexical)
{
    if ((lexical(pwChar[s->start])==lex_Ra) && s->end > s->start && lexical(pwChar[s->start+1]) == lex_Halant)
        return (SHAPE_does_GSUB_feature_apply_to_chars(hdc, psa, psc, &pwChar[s->start], 1, 2, "rphf") > 0);
    return FALSE;
}