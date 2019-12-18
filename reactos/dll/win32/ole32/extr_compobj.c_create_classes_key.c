#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  attr ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  UNICODE_STRING ;
struct TYPE_3__ {int Length; int /*<<< orphan*/ * SecurityQualityOfService; int /*<<< orphan*/ * SecurityDescriptor; scalar_t__ Attributes; int /*<<< orphan*/ * ObjectName; int /*<<< orphan*/  RootDirectory; } ;
typedef  int /*<<< orphan*/  REGSAM ;
typedef  TYPE_1__ OBJECT_ATTRIBUTES ;
typedef  int /*<<< orphan*/  LSTATUS ;
typedef  int /*<<< orphan*/  HKEY ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_INVALID_HANDLE ; 
 int /*<<< orphan*/  RtlInitUnicodeString (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  RtlNtStatusToDosError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_key (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  get_classes_root_hkey (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

LSTATUS create_classes_key( HKEY hkey, const WCHAR *name, REGSAM access, HKEY *retkey )
{
    OBJECT_ATTRIBUTES attr;
    UNICODE_STRING nameW;

    if (!(hkey = get_classes_root_hkey( hkey, access ))) return ERROR_INVALID_HANDLE;

    attr.Length = sizeof(attr);
    attr.RootDirectory = hkey;
    attr.ObjectName = &nameW;
    attr.Attributes = 0;
    attr.SecurityDescriptor = NULL;
    attr.SecurityQualityOfService = NULL;
    RtlInitUnicodeString( &nameW, name );

    return RtlNtStatusToDosError( create_key( retkey, access, &attr ) );
}