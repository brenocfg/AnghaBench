#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_4__ {int /*<<< orphan*/ * title; int /*<<< orphan*/  filename; } ;
typedef  TYPE_1__ SearchItem ;

/* Variables and functions */
 int /*<<< orphan*/  heap_alloc (int) ; 
 TYPE_1__* heap_alloc_zero (int) ; 
 int lstrlenW (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static SearchItem *alloc_search_item(WCHAR *title, const WCHAR *filename)
{
    int filename_len = filename ? (lstrlenW(filename)+1)*sizeof(WCHAR) : 0;
    SearchItem *item;

    item = heap_alloc_zero(sizeof(SearchItem));
    if(filename)
    {
        item->filename = heap_alloc(filename_len);
        memcpy(item->filename, filename, filename_len);
    }
    item->title = title; /* Already allocated */

    return item;
}