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
typedef  int /*<<< orphan*/  SID_NAME_USE ;
typedef  scalar_t__ PSID ;
typedef  char* LPSTR ;
typedef  int DWORD ;

/* Variables and functions */
 char* ACE4_GROUP ; 
 char* ACE4_NOBODY ; 
 char* ACE4_OWNER ; 
 int /*<<< orphan*/  ACLLVL ; 
 int ERROR_INSUFFICIENT_BUFFER ; 
 int ERROR_INTERNAL_ERROR ; 
 int ERROR_SUCCESS ; 
 scalar_t__ EqualSid (scalar_t__,scalar_t__) ; 
 int GetLastError () ; 
 int LookupAccountSid (int /*<<< orphan*/ *,scalar_t__,char*,int*,char*,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  eprintf (char*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int is_well_known_sid (scalar_t__,char*) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 

__attribute__((used)) static int map_nfs4ace_who(PSID sid, PSID owner_sid, PSID group_sid, char *who_out, char *domain)
{
    int status = ERROR_INTERNAL_ERROR;
    DWORD size = 0, tmp_size = 0;
    SID_NAME_USE sid_type;
    LPSTR tmp_buf = NULL, who = NULL;

    /* for ace mapping, we want to map owner's sid into "owner@" 
     * but for set_owner attribute we want to map owner into a user name
     * same applies to group
     */
    status = 0;
    if (owner_sid) {
        if (EqualSid(sid, owner_sid)) {
            dprintf(ACLLVL, "map_nfs4ace_who: this is owner's sid\n");
            memcpy(who_out, ACE4_OWNER, strlen(ACE4_OWNER)+1); 
            return ERROR_SUCCESS;
        }
    }
    if (group_sid) {
        if (EqualSid(sid, group_sid)) {
            dprintf(ACLLVL, "map_nfs4ace_who: this is group's sid\n");
            memcpy(who_out, ACE4_GROUP, strlen(ACE4_GROUP)+1); 
            return ERROR_SUCCESS;
        }
    }
    status = is_well_known_sid(sid, who_out);
    if (status) {
        if (!strncmp(who_out, ACE4_NOBODY, strlen(ACE4_NOBODY))) {
            size = (DWORD)strlen(ACE4_NOBODY);
            goto add_domain;
        }
        else
            return ERROR_SUCCESS;
    }

    status = LookupAccountSid(NULL, sid, who, &size, tmp_buf, 
        &tmp_size, &sid_type);
    dprintf(ACLLVL, "map_nfs4ace_who: LookupAccountSid returned %d GetLastError "
            "%d name len %d domain len %d\n", status, GetLastError(), 
            size, tmp_size); 
    if (status)
        return ERROR_INTERNAL_ERROR;
    status = GetLastError();
    if (status != ERROR_INSUFFICIENT_BUFFER)
        return ERROR_INTERNAL_ERROR;
    who = malloc(size);
    if (who == NULL) {
        status = GetLastError();
        goto out;
    }
    tmp_buf = malloc(tmp_size);
    if (tmp_buf == NULL)
        goto out_free_who;
    status = LookupAccountSid(NULL, sid, who, &size, tmp_buf, 
                                &tmp_size, &sid_type);
    free(tmp_buf);
    if (!status) {
        eprintf("map_nfs4ace_who: LookupAccountSid failed with %d\n", 
                GetLastError());
        goto out_free_who;
    }
    memcpy(who_out, who, size);
add_domain:
    memcpy(who_out+size, "@", sizeof(char));
    memcpy(who_out+size+1, domain, strlen(domain)+1);
    dprintf(ACLLVL, "map_nfs4ace_who: who=%s\n", who_out);
    if (who) free(who);
    status = ERROR_SUCCESS;
out:
    return status;
out_free_who:
    free(who);
    status = GetLastError();
    goto out;
}