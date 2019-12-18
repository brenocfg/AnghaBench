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
struct class_categories {int size; int impl_offset; int req_offset; } ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int ULONG ;
typedef  int /*<<< orphan*/  CATID ;

/* Variables and functions */
 int CHARS_IN_GUID ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 struct class_categories* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  StringFromGUID2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static struct class_categories *COMCAT_PrepareClassCategories(
    ULONG impl_count, const CATID *impl_catids, ULONG req_count, const CATID *req_catids)
{
    struct class_categories *categories;
    WCHAR *strings;
    ULONG size;

    size = sizeof(struct class_categories) + ((impl_count + req_count)*CHARS_IN_GUID + 2)*sizeof(WCHAR);
    categories = HeapAlloc(GetProcessHeap(), 0, size);
    if (categories == NULL) return categories;

    categories->size = size;
    categories->impl_offset = sizeof(struct class_categories);
    categories->req_offset = categories->impl_offset + (impl_count*CHARS_IN_GUID + 1)*sizeof(WCHAR);

    strings = (WCHAR *)(categories + 1);
    while (impl_count--) {
	StringFromGUID2(impl_catids++, strings, CHARS_IN_GUID);
	strings += CHARS_IN_GUID;
    }
    *strings++ = 0;

    while (req_count--) {
	StringFromGUID2(req_catids++, strings, CHARS_IN_GUID);
	strings += CHARS_IN_GUID;
    }
    *strings++ = 0;

    return categories;
}