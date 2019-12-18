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
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  GUID ;

/* Variables and functions */
 int /*<<< orphan*/  CLSIDFromString (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lstrcpyW (char*,char const*) ; 

__attribute__((used)) static HRESULT string_to_guid(const WCHAR *string, GUID *guid)
{
    WCHAR buffer[39];
    buffer[0] = '{';
    lstrcpyW(buffer + 1, string);
    buffer[37] = '}';
    buffer[38] = 0;
    return CLSIDFromString(buffer, guid);
}