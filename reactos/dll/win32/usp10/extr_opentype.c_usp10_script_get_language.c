#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ tag; } ;
struct TYPE_5__ {size_t language_count; TYPE_2__* languages; } ;
typedef  scalar_t__ OPENTYPE_TAG ;
typedef  TYPE_1__ LoadedScript ;
typedef  TYPE_2__ LoadedLanguage ;

/* Variables and functions */

__attribute__((used)) static LoadedLanguage *usp10_script_get_language(LoadedScript *script, OPENTYPE_TAG tag)
{
    size_t i;

    for (i = 0; i < script->language_count; ++i)
    {
        if (script->languages[i].tag == tag)
            return &script->languages[i];
    }

    return NULL;
}