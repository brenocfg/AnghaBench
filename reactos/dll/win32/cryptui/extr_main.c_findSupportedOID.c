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
struct OIDToString {int /*<<< orphan*/  oid; } ;
typedef  int /*<<< orphan*/  LPCSTR ;

/* Variables and functions */
 int ARRAY_SIZE (struct OIDToString*) ; 
 struct OIDToString* oidMap ; 
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct OIDToString *findSupportedOID(LPCSTR oid)
{
    int indexHigh = ARRAY_SIZE(oidMap) - 1, indexLow = 0;

    while (indexLow <= indexHigh)
    {
        int cmp, i = (indexLow + indexHigh) / 2;
        if (!(cmp = strcmp(oid, oidMap[i].oid)))
            return &oidMap[i];
        if (cmp > 0)
            indexLow = i + 1;
        else
            indexHigh = i - 1;
    }
    return NULL;
}