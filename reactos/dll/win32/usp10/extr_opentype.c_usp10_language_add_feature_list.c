#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {char tableType; int lookup_count; int* lookups; TYPE_4__ const* feature; int /*<<< orphan*/  tag; } ;
struct TYPE_14__ {unsigned int feature_count; TYPE_6__* features; int /*<<< orphan*/  features_size; } ;
struct TYPE_13__ {int /*<<< orphan*/ * LookupListIndex; int /*<<< orphan*/  LookupCount; } ;
struct TYPE_12__ {TYPE_2__* FeatureRecord; } ;
struct TYPE_11__ {int /*<<< orphan*/ * FeatureTag; int /*<<< orphan*/  Feature; } ;
struct TYPE_10__ {int /*<<< orphan*/ * FeatureIndex; int /*<<< orphan*/  FeatureCount; } ;
typedef  TYPE_1__ OT_LangSys ;
typedef  TYPE_2__ OT_FeatureRecord ;
typedef  TYPE_3__ OT_FeatureList ;
typedef  TYPE_4__ OT_Feature ;
typedef  TYPE_5__ LoadedLanguage ;
typedef  TYPE_6__ LoadedFeature ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int GET_BE_WORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MS_MAKE_TAG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,char,unsigned int) ; 
 int* heap_calloc (int,int) ; 
 int /*<<< orphan*/  usp10_array_reserve (void**,int /*<<< orphan*/ *,unsigned int,int) ; 

__attribute__((used)) static void usp10_language_add_feature_list(LoadedLanguage *language, char table_type,
        const OT_LangSys *lang, const OT_FeatureList *feature_list)
{
    unsigned int count = GET_BE_WORD(lang->FeatureCount);
    unsigned int i, j;

    TRACE("table_type %#x, %u features.\n", table_type, count);

    if (!count || !usp10_array_reserve((void **)&language->features, &language->features_size,
            language->feature_count + count, sizeof(*language->features)))
        return;

    for (i = 0; i < count; ++i)
    {
        const OT_FeatureRecord *record;
        LoadedFeature *loaded_feature;
        const OT_Feature *feature;

        record = &feature_list->FeatureRecord[GET_BE_WORD(lang->FeatureIndex[i])];
        feature = (const OT_Feature *)((const BYTE *)feature_list + GET_BE_WORD(record->Feature));

        loaded_feature = &language->features[language->feature_count + i];
        loaded_feature->tag = MS_MAKE_TAG(record->FeatureTag[0], record->FeatureTag[1],
                record->FeatureTag[2], record->FeatureTag[3]);
        loaded_feature->tableType = table_type;
        loaded_feature->feature = feature;
        loaded_feature->lookup_count = GET_BE_WORD(feature->LookupCount);
        loaded_feature->lookups = heap_calloc(loaded_feature->lookup_count, sizeof(*loaded_feature->lookups));
        for (j = 0; j < loaded_feature->lookup_count; ++j)
            loaded_feature->lookups[j] = GET_BE_WORD(feature->LookupListIndex[j]);
    }
    language->feature_count += count;
}