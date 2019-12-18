#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_5__ {int NameOffset; int /*<<< orphan*/  Id; int /*<<< orphan*/  NameIsString; } ;
struct TYPE_4__ {int Length; int /*<<< orphan*/  NameString; } ;
typedef  scalar_t__* LPWSTR ;
typedef  TYPE_1__ IMAGE_RESOURCE_DIR_STRING_U ;
typedef  TYPE_2__ IMAGE_RESOURCE_DIRECTORY_ENTRY ;
typedef  int /*<<< orphan*/  IMAGE_RESOURCE_DIRECTORY ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 scalar_t__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__* UIntToPtr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static LPWSTR resource_dup_string( const IMAGE_RESOURCE_DIRECTORY *root, const IMAGE_RESOURCE_DIRECTORY_ENTRY *entry )
{
    const IMAGE_RESOURCE_DIR_STRING_U* string;
    LPWSTR s;

    if (!entry->NameIsString)
        return UIntToPtr(entry->Id);

    string = (const IMAGE_RESOURCE_DIR_STRING_U*) (((const char *)root) + entry->NameOffset);
    s = HeapAlloc(GetProcessHeap(), 0, (string->Length + 1)*sizeof (WCHAR) );
    memcpy( s, string->NameString, (string->Length + 1)*sizeof (WCHAR) );
    s[string->Length] = 0;

    return s;
}