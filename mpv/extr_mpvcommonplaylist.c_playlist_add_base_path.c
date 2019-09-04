#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct playlist_entry {char* filename; struct playlist_entry* next; } ;
struct playlist {struct playlist_entry* first; } ;
struct TYPE_5__ {scalar_t__ len; } ;
typedef  TYPE_1__ bstr ;

/* Variables and functions */
 int /*<<< orphan*/  bstr0 (char*) ; 
 scalar_t__ bstrcmp0 (TYPE_1__,char*) ; 
 int /*<<< orphan*/  mp_is_url (int /*<<< orphan*/ ) ; 
 char* mp_path_join_bstr (struct playlist_entry*,TYPE_1__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  talloc_free (char*) ; 

void playlist_add_base_path(struct playlist *pl, bstr base_path)
{
    if (base_path.len == 0 || bstrcmp0(base_path, ".") == 0)
        return;
    for (struct playlist_entry *e = pl->first; e; e = e->next) {
        if (!mp_is_url(bstr0(e->filename))) {
            char *new_file = mp_path_join_bstr(e, base_path, bstr0(e->filename));
            talloc_free(e->filename);
            e->filename = new_file;
        }
    }
}