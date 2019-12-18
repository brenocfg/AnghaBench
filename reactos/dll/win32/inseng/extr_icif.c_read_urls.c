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
struct url_info {int index; int /*<<< orphan*/  entry; int /*<<< orphan*/  flags; int /*<<< orphan*/ * url; } ;
struct inf_value {int dummy; } ;
struct inf_section {int dummy; } ;
struct cifcomponent {int /*<<< orphan*/  urls; } ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 struct url_info* heap_alloc_zero (int) ; 
 int /*<<< orphan*/  heap_free (char*) ; 
 scalar_t__ inf_section_next_value (struct inf_section*,struct inf_value**) ; 
 char* inf_value_get_key (struct inf_value*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strncasecmp (char*,char*,int) ; 
 int strtol (char*,char**,int) ; 
 int /*<<< orphan*/  url_entry_free (struct url_info*) ; 
 int /*<<< orphan*/  value_get_dword_field (struct inf_value*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  value_get_str_field (struct inf_value*,int,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL read_urls(struct cifcomponent *component, struct inf_section *section)
{
    struct inf_value *inf_value = NULL;
    struct url_info *url_entry;
    char *str, *next;
    int index;

    while (inf_section_next_value(section, &inf_value))
    {
        str = inf_value_get_key(inf_value);
        if (!str) return E_OUTOFMEMORY;

        if (strncasecmp(str, "URL", 3))
            goto next;

        if (!str[3])
            goto next;

        index = strtol(str+3, &next, 10);
        if (next == str+3 || *next != 0 || index < 1)
            goto next;
        index--;

        url_entry = heap_alloc_zero(sizeof(*url_entry));
        if (!url_entry) goto error;

        url_entry->index = index;

        if (!value_get_str_field(inf_value, 1, &url_entry->url, NULL))
            goto error;
        if (!url_entry->url || !*url_entry->url)
        {
            url_entry_free(url_entry);
            goto next;
        }

        if (!value_get_dword_field(inf_value, 2, &url_entry->flags, 0))
            goto error;

        list_add_tail(&component->urls, &url_entry->entry);

    next:
        heap_free(str);
    }

    return TRUE;

error:
    heap_free(str);
    url_entry_free(url_entry);
    return FALSE;
}