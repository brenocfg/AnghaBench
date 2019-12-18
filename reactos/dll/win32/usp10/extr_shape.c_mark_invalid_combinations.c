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
typedef  scalar_t__ (* combining_lexical_function ) (int const) ;
typedef  int /*<<< orphan*/  WORD ;
typedef  int WCHAR ;
typedef  int INT ;
typedef  int /*<<< orphan*/  HDC ;
typedef  scalar_t__ CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  GetGlyphIndicesW (int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__* heap_alloc (int) ; 
 int /*<<< orphan*/  heap_free (scalar_t__*) ; 
 int /*<<< orphan*/  insert_glyph (int /*<<< orphan*/ *,int*,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mark_invalid_combinations(HDC hdc, const WCHAR* pwcChars, INT cChars, WORD *pwGlyphs, INT *pcGlyphs, INT write_dir, WORD *pwLogClust, combining_lexical_function lex)
{
    CHAR *context_type;
    int i,g;
    WCHAR invalid = 0x25cc;
    WORD invalid_glyph;

    context_type = heap_alloc(cChars);

    /* Mark invalid combinations */
    for (i = 0; i < cChars; i++)
       context_type[i] = lex(pwcChars[i]);

    GetGlyphIndicesW(hdc, &invalid, 1, &invalid_glyph, 0);
    for (i = 1, g=1; i < cChars - 1; i++, g++)
    {
        if (context_type[i] != 0 && context_type[i+write_dir]==context_type[i])
        {
            insert_glyph(pwGlyphs, pcGlyphs, cChars, write_dir, invalid_glyph, g, pwLogClust);
            g++;
        }
    }

    heap_free(context_type);
}