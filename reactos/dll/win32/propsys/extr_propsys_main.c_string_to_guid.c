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
struct TYPE_3__ {int Data1; int Data2; int Data3; int* Data4; } ;
typedef  TYPE_1__* LPGUID ;
typedef  size_t* LPCWSTR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int* hex2bin ; 
 int /*<<< orphan*/  validate_indices (size_t*,int,int) ; 

__attribute__((used)) static BOOL string_to_guid(LPCWSTR s, LPGUID id)
{
    /* in form {XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX} */

    if (!validate_indices(s, 0, 8)) return FALSE;
    id->Data1 = (hex2bin[s[1]] << 28 | hex2bin[s[2]] << 24 | hex2bin[s[3]] << 20 | hex2bin[s[4]] << 16 |
                 hex2bin[s[5]] << 12 | hex2bin[s[6]] << 8  | hex2bin[s[7]] << 4  | hex2bin[s[8]]);
    if (!validate_indices(s, 9, 14)) return FALSE;
    id->Data2 = hex2bin[s[10]] << 12 | hex2bin[s[11]] << 8 | hex2bin[s[12]] << 4 | hex2bin[s[13]];
    if (!validate_indices(s, 15, 19)) return FALSE;
    id->Data3 = hex2bin[s[15]] << 12 | hex2bin[s[16]] << 8 | hex2bin[s[17]] << 4 | hex2bin[s[18]];

    /* these are just sequential bytes */

    if (!validate_indices(s, 20, 21)) return FALSE;
    id->Data4[0] = hex2bin[s[20]] << 4 | hex2bin[s[21]];
    if (!validate_indices(s, 22, 24)) return FALSE;
    id->Data4[1] = hex2bin[s[22]] << 4 | hex2bin[s[23]];

    if (!validate_indices(s, 25, 26)) return FALSE;
    id->Data4[2] = hex2bin[s[25]] << 4 | hex2bin[s[26]];
    if (!validate_indices(s, 27, 28)) return FALSE;
    id->Data4[3] = hex2bin[s[27]] << 4 | hex2bin[s[28]];
    if (!validate_indices(s, 29, 30)) return FALSE;
    id->Data4[4] = hex2bin[s[29]] << 4 | hex2bin[s[30]];
    if (!validate_indices(s, 31, 32)) return FALSE;
    id->Data4[5] = hex2bin[s[31]] << 4 | hex2bin[s[32]];
    if (!validate_indices(s, 33, 34)) return FALSE;
    id->Data4[6] = hex2bin[s[33]] << 4 | hex2bin[s[34]];
    if (!validate_indices(s, 35, 37)) return FALSE;
    id->Data4[7] = hex2bin[s[35]] << 4 | hex2bin[s[36]];

    return TRUE;
}