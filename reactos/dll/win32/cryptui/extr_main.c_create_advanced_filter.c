#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {size_t cUsageIdentifier; struct TYPE_16__* rgpszUsageIdentifier; } ;
struct TYPE_15__ {scalar_t__ pszOID; } ;
typedef  TYPE_1__* PCCRYPT_OID_INFO ;
typedef  TYPE_2__* LPSTR ;
typedef  size_t DWORD ;
typedef  TYPE_2__ CERT_ENHKEY_USAGE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 TYPE_2__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ TRUE ; 
 scalar_t__ WTHelperGetKnownUsages (int,TYPE_1__***) ; 
 TYPE_2__* add_oid_to_usage (TYPE_2__*,TYPE_2__*) ; 
 TYPE_2__* convert_usages_str_to_usage (TYPE_2__*) ; 
 TYPE_2__* get_cert_mgr_usages () ; 
 int /*<<< orphan*/  strcmp (TYPE_2__,scalar_t__) ; 

__attribute__((used)) static CERT_ENHKEY_USAGE *create_advanced_filter(void)
{
    CERT_ENHKEY_USAGE *advancedUsage = HeapAlloc(GetProcessHeap(),
     HEAP_ZERO_MEMORY, sizeof(CERT_ENHKEY_USAGE));

    if (advancedUsage)
    {
        PCCRYPT_OID_INFO *usages;

        if (WTHelperGetKnownUsages(1, &usages))
        {
            LPSTR disabledUsagesStr;

            if ((disabledUsagesStr = get_cert_mgr_usages()))
            {
                CERT_ENHKEY_USAGE *disabledUsages =
                 convert_usages_str_to_usage(disabledUsagesStr);

                if (disabledUsages)
                {
                    PCCRYPT_OID_INFO *ptr;

                    for (ptr = usages; advancedUsage && *ptr; ptr++)
                    {
                        DWORD i;
                        BOOL disabled = FALSE;

                        for (i = 0; !disabled &&
                         i < disabledUsages->cUsageIdentifier; i++)
                            if (!strcmp(disabledUsages->rgpszUsageIdentifier[i],
                             (*ptr)->pszOID))
                                disabled = TRUE;
                        if (!disabled)
                            advancedUsage = add_oid_to_usage(advancedUsage,
                             (LPSTR)(*ptr)->pszOID);
                    }
                    /* The individual strings are pointers to disabledUsagesStr,
                     * so they're freed when it is.
                     */
                    HeapFree(GetProcessHeap(), 0,
                     disabledUsages->rgpszUsageIdentifier);
                    HeapFree(GetProcessHeap(), 0, disabledUsages);
                }
                HeapFree(GetProcessHeap(), 0, disabledUsagesStr);
            }
            WTHelperGetKnownUsages(2, &usages);
        }
    }
    return advancedUsage;
}