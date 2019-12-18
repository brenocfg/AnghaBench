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
typedef  scalar_t__ WCHAR ;
typedef  scalar_t__* PWSTR ;
typedef  int /*<<< orphan*/ * PBOOLEAN ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ UNICODE_NULL ; 
 scalar_t__ wcscmp (scalar_t__*,scalar_t__*) ; 

DWORD
FindSymbolicLinkEntry(
    PWSTR NameToFind,
    PWSTR NamesList,
    DWORD TotalEntries,
    PBOOLEAN Found)
{
    WCHAR Current;
    DWORD Entries;
    PWSTR PartialNamesList;

    /* We need all parameters to be set */
    if (NameToFind == NULL || NamesList == NULL || Found == NULL)
    {
        return ERROR_INVALID_PARAMETER;
    }

    /* Assume failure */
    *Found = FALSE;

    /* If no entries, job done, nothing found */
    if (TotalEntries == 0)
    {
        return ERROR_SUCCESS;
    }

    /* Start browsing the names list */
    Entries = 0;
    PartialNamesList = NamesList;
    /* As long as we didn't find the name... */
    while (wcscmp(NameToFind, PartialNamesList) != 0)
    {
        /* We chomped an entry! */
        ++Entries;

        /* We're out of entries, bail out not to overrun */
        if (Entries > TotalEntries)
        {
            /*
             * Even though we found nothing,
             * the function ran fine
             */
            return ERROR_SUCCESS;
        }

        /* Jump to the next string */
        do
        {
            Current = *PartialNamesList;
            ++PartialNamesList;
        } while (Current != UNICODE_NULL);
    }

    /*
     * We're here because the loop stopped:
     * it means we found the name in the list
     */
    *Found = TRUE;
    return ERROR_SUCCESS;
}