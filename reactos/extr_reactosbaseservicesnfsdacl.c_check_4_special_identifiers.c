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
typedef  int /*<<< orphan*/  PSID ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  ACE4_EVERYONE ; 
 int /*<<< orphan*/  ACE4_GROUP ; 
 int /*<<< orphan*/  ACE4_NOBODY ; 
 int /*<<< orphan*/  ACE4_OWNER ; 
 int ERROR_SUCCESS ; 
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  WinCreatorGroupSid ; 
 int /*<<< orphan*/  WinCreatorOwnerSid ; 
 int /*<<< orphan*/  WinNullSid ; 
 int /*<<< orphan*/  WinWorldSid ; 
 int create_unknownsid (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (char*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int check_4_special_identifiers(char *who, PSID *sid, DWORD *sid_len, 
                                       BOOLEAN *flag)
{
    int status = ERROR_SUCCESS;
    WELL_KNOWN_SID_TYPE type = 0;
    *flag = TRUE;
    if (!strncmp(who, ACE4_OWNER, strlen(ACE4_OWNER)-1))
        type = WinCreatorOwnerSid;
    else if (!strncmp(who, ACE4_GROUP, strlen(ACE4_GROUP)-1))
        type = WinCreatorGroupSid;
    else if (!strncmp(who, ACE4_EVERYONE, strlen(ACE4_EVERYONE)-1))
        type = WinWorldSid;
    else if (!strncmp(who, ACE4_NOBODY, strlen(ACE4_NOBODY)))
        type = WinNullSid;
    else 
        *flag = FALSE;
    if (*flag) 
        status = create_unknownsid(type, sid, sid_len);
    return status;
}