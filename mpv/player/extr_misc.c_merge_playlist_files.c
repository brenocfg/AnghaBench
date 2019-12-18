#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct playlist_entry {char* filename; struct playlist_entry* next; } ;
struct playlist {struct playlist_entry* first; } ;
struct TYPE_2__ {scalar_t__ len; } ;

/* Variables and functions */
 int /*<<< orphan*/  bstr0 (char*) ; 
 TYPE_1__ bstr_strip (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  playlist_add_file (struct playlist*,char*) ; 
 int /*<<< orphan*/  playlist_clear (struct playlist*) ; 
 size_t strcspn (char*,char*) ; 
 scalar_t__ strlen (char*) ; 
 char* talloc_asprintf_append_buffer (char*,char*,scalar_t__) ; 
 int /*<<< orphan*/  talloc_free (char*) ; 
 char* talloc_strdup (int /*<<< orphan*/ *,char*) ; 
 char* talloc_strdup_append_buffer (char*,char*) ; 

void merge_playlist_files(struct playlist *pl)
{
    if (!pl->first)
        return;
    char *edl = talloc_strdup(NULL, "edl://");
    for (struct playlist_entry *e = pl->first; e; e = e->next) {
        if (e != pl->first)
            edl = talloc_strdup_append_buffer(edl, ";");
        // Escape if needed
        if (e->filename[strcspn(e->filename, "=%,;\n")] ||
            bstr_strip(bstr0(e->filename)).len != strlen(e->filename))
        {
            // %length%
            edl = talloc_asprintf_append_buffer(edl, "%%%zd%%", strlen(e->filename));
        }
        edl = talloc_strdup_append_buffer(edl, e->filename);
    }
    playlist_clear(pl);
    playlist_add_file(pl, edl);
    talloc_free(edl);
}