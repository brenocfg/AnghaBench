#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int cbSize; } ;
struct TYPE_15__ {int /*<<< orphan*/  script_cache; int /*<<< orphan*/ * font_cache; int /*<<< orphan*/  tm; int /*<<< orphan*/  fmt; } ;
struct TYPE_14__ {TYPE_1__* pBuffer; } ;
struct TYPE_13__ {TYPE_3__* pDefaultStyle; } ;
typedef  TYPE_2__ ME_TextEditor ;
typedef  TYPE_3__ ME_Style ;
typedef  TYPE_4__ CHARFORMAT2W ;

/* Variables and functions */
 TYPE_3__* ME_ApplyStyle (TYPE_2__*,TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  ME_MarkAllForWrapping (TYPE_2__*) ; 
 int /*<<< orphan*/  ME_ReleaseStyle (TYPE_3__*) ; 
 int /*<<< orphan*/  ScriptFreeCache (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  release_font_cache (int /*<<< orphan*/ *) ; 

void ME_SetDefaultCharFormat(ME_TextEditor *editor, CHARFORMAT2W *mod)
{
    ME_Style *style, *def = editor->pBuffer->pDefaultStyle;

    assert(mod->cbSize == sizeof(CHARFORMAT2W));
    style = ME_ApplyStyle(editor, def, mod);
    def->fmt = style->fmt;
    def->tm = style->tm;
    if (def->font_cache)
    {
        release_font_cache( def->font_cache );
        def->font_cache = NULL;
    }
    ScriptFreeCache( &def->script_cache );
    ME_ReleaseStyle( style );
    ME_MarkAllForWrapping( editor );
}