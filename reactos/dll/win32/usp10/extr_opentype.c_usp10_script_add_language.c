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
struct TYPE_6__ {int /*<<< orphan*/  tag; } ;
struct TYPE_5__ {scalar_t__ language_count; TYPE_2__* languages; int /*<<< orphan*/  languages_size; } ;
typedef  int /*<<< orphan*/  OPENTYPE_TAG ;
typedef  TYPE_1__ LoadedScript ;
typedef  TYPE_2__ LoadedLanguage ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  usp10_array_reserve (void**,int /*<<< orphan*/ *,scalar_t__,int) ; 

__attribute__((used)) static LoadedLanguage *usp10_script_add_language(LoadedScript *script, OPENTYPE_TAG tag)
{
    LoadedLanguage *language;

    if (!usp10_array_reserve((void **)&script->languages, &script->languages_size,
            script->language_count + 1, sizeof(*script->languages)))
    {
        ERR("Failed to grow languages array.\n");
        return NULL;
    }

    language = &script->languages[script->language_count++];
    language->tag = tag;

    return language;
}