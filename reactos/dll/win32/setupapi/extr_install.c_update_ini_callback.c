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
typedef  int /*<<< orphan*/  section ;
typedef  int /*<<< orphan*/  filename ;
typedef  int /*<<< orphan*/  buffer ;
typedef  scalar_t__ WCHAR ;
typedef  int /*<<< orphan*/  PCWSTR ;
typedef  scalar_t__* LPWSTR ;
typedef  int /*<<< orphan*/  INFCONTEXT ;
typedef  int /*<<< orphan*/  HINF ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int MAX_INF_STRING_LENGTH ; 
 scalar_t__ SetupFindFirstLineW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ SetupFindNextLine (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetupGetStringFieldW (int /*<<< orphan*/ *,int,scalar_t__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  WritePrivateProfileStringW (scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  debugstr_w (scalar_t__*) ; 
 scalar_t__* strchrW (scalar_t__*,char) ; 
 int /*<<< orphan*/  strcpyW (scalar_t__*,scalar_t__*) ; 

__attribute__((used)) static BOOL update_ini_callback( HINF hinf, PCWSTR field, void *arg )
{
    INFCONTEXT context;

    BOOL ok = SetupFindFirstLineW( hinf, field, NULL, &context );

    for (; ok; ok = SetupFindNextLine( &context, &context ))
    {
        WCHAR buffer[MAX_INF_STRING_LENGTH];
        WCHAR  filename[MAX_INF_STRING_LENGTH];
        WCHAR  section[MAX_INF_STRING_LENGTH];
        WCHAR  entry[MAX_INF_STRING_LENGTH];
        WCHAR  string[MAX_INF_STRING_LENGTH];
        LPWSTR divider;

        if (!SetupGetStringFieldW( &context, 1, filename,
                                   sizeof(filename)/sizeof(WCHAR), NULL ))
            continue;

        if (!SetupGetStringFieldW( &context, 2, section,
                                   sizeof(section)/sizeof(WCHAR), NULL ))
            continue;

        if (!SetupGetStringFieldW( &context, 4, buffer,
                                   sizeof(buffer)/sizeof(WCHAR), NULL ))
            continue;

        divider = strchrW(buffer,'=');
        if (divider)
        {
            *divider = 0;
            strcpyW(entry,buffer);
            divider++;
            strcpyW(string,divider);
        }
        else
        {
            strcpyW(entry,buffer);
            string[0]=0;
        }

        TRACE("Writing %s = %s in %s of file %s\n",debugstr_w(entry),
               debugstr_w(string),debugstr_w(section),debugstr_w(filename));
        WritePrivateProfileStringW(section,entry,string,filename);

    }
    return TRUE;
}