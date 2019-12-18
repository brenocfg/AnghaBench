#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  tag; } ;
struct TYPE_9__ {int script_count; TYPE_1__* scripts; } ;
struct TYPE_8__ {int /*<<< orphan*/  tag; } ;
typedef  TYPE_2__ ScriptCache ;
typedef  int /*<<< orphan*/  OPENTYPE_TAG ;
typedef  TYPE_3__ LoadedScript ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  USP_E_SCRIPT_NOT_IN_FONT ; 
 int /*<<< orphan*/  _initialize_script_cache (TYPE_2__*) ; 
 int min (int,int) ; 
 TYPE_3__* usp10_script_cache_get_script (TYPE_2__*,int /*<<< orphan*/ ) ; 

HRESULT OpenType_GetFontScriptTags(ScriptCache *psc, OPENTYPE_TAG searchingFor, int cMaxTags, OPENTYPE_TAG *pScriptTags, int *pcTags)
{
    int i;
    const LoadedScript *script;
    HRESULT rc = S_OK;

    _initialize_script_cache(psc);

    *pcTags = psc->script_count;

    if (searchingFor)
    {
        if (!(script = usp10_script_cache_get_script(psc, searchingFor)))
            return USP_E_SCRIPT_NOT_IN_FONT;

        *pScriptTags = script->tag;
        *pcTags = 1;
        return S_OK;
    }

    if (cMaxTags < *pcTags)
        rc = E_OUTOFMEMORY;

    cMaxTags = min(cMaxTags, psc->script_count);
    for (i = 0; i < cMaxTags; ++i)
    {
        pScriptTags[i] = psc->scripts[i].tag;
    }
    return rc;
}