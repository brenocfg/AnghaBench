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
typedef  int /*<<< orphan*/  WELL_KNOWN_SID_TYPE ;
typedef  int /*<<< orphan*/ * PSID ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ACLLVL ; 
 int CreateWellKnownSid (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 int ERROR_INSUFFICIENT_BUFFER ; 
 int ERROR_INTERNAL_ERROR ; 
 int ERROR_SUCCESS ; 
 int GetLastError () ; 
 int /*<<< orphan*/  dprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int,scalar_t__) ; 
 int /*<<< orphan*/  eprintf (char*,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (scalar_t__) ; 

__attribute__((used)) static int create_unknownsid(WELL_KNOWN_SID_TYPE type, PSID *sid, 
                             DWORD *sid_len)
{
    int status;
    *sid_len = 0;
    *sid = NULL;

    status = CreateWellKnownSid(type, NULL, *sid, sid_len);
    dprintf(ACLLVL, "create_unknownsid: CreateWellKnownSid type %d returned %d "
            "GetLastError %d sid len %d needed\n", type, status, 
            GetLastError(), *sid_len); 
    if (status) 
        return ERROR_INTERNAL_ERROR;
    status = GetLastError();
    if (status != ERROR_INSUFFICIENT_BUFFER) 
        return status;
    *sid = malloc(*sid_len);
    if (*sid == NULL) 
        return ERROR_INSUFFICIENT_BUFFER;
    status = CreateWellKnownSid(type, NULL, *sid, sid_len);
    if (status) 
        return ERROR_SUCCESS;
    free(*sid);
    status = GetLastError();
    eprintf("create_unknownsid: CreateWellKnownSid failed with %d\n", status);
    return status;
}