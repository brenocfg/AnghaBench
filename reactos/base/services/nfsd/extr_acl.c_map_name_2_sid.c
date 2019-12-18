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
typedef  int /*<<< orphan*/ * PSID ;
typedef  int /*<<< orphan*/ * LPSTR ;
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ACLLVL ; 
 int /*<<< orphan*/  ConvertSidToStringSidA (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
#define  ERROR_INSUFFICIENT_BUFFER 129 
 int ERROR_INTERNAL_ERROR ; 
#define  ERROR_NONE_MAPPED 128 
 int ERROR_SUCCESS ; 
 int GetLastError () ; 
 int /*<<< orphan*/  IsValidSid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ *) ; 
 int LookupAccountName (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WinNullSid ; 
 int create_unknownsid (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dprintf (int,char*,...) ; 
 int /*<<< orphan*/  eprintf (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int map_name_2_sid(DWORD *sid_len, PSID *sid, LPCSTR name)
{
    int status = ERROR_INTERNAL_ERROR;
    SID_NAME_USE sid_type;
    LPSTR tmp_buf = NULL;
    DWORD tmp = 0;

    status = LookupAccountName(NULL, name, NULL, sid_len, NULL, &tmp, &sid_type);
    dprintf(ACLLVL, "map_name_2_sid: LookupAccountName for %s returned %d "
            "GetLastError %d name len %d domain len %d\n", name, status, 
            GetLastError(), *sid_len, tmp); 
    if (status)
        return ERROR_INTERNAL_ERROR;

    status = GetLastError();
    switch(status) {
    case ERROR_INSUFFICIENT_BUFFER:
        *sid = malloc(*sid_len);
        if (*sid == NULL) {
            status = GetLastError();
            goto out;
        }
        tmp_buf = (LPSTR) malloc(tmp);
        if (tmp_buf == NULL)
            goto out_free_sid;
        status = LookupAccountName(NULL, name, *sid, sid_len, tmp_buf, 
                                    &tmp, &sid_type);
        free(tmp_buf);
        if (!status) {
            eprintf("map_name_2_sid: LookupAccountName for %s failed "
                    "with %d\n", name, GetLastError());
            goto out_free_sid;
        } else {
#ifdef DEBUG_ACLS
            LPSTR ssid = NULL;
            if (IsValidSid(*sid))
                if (ConvertSidToStringSidA(*sid, &ssid))
                    dprintf(1, "map_name_2_sid: sid_type = %d SID %s\n", 
                            sid_type, ssid);
                else
                    dprintf(1, "map_name_2_sid: ConvertSidToStringSidA failed "
                            "with %d\n", GetLastError());
            else
                dprintf(1, "map_name_2_sid: Invalid Sid ?\n");
            if (ssid) LocalFree(ssid);
#endif
        }
        status = ERROR_SUCCESS;
        break;
    case ERROR_NONE_MAPPED:
        status = create_unknownsid(WinNullSid, sid, sid_len);
        if (status)
            goto out_free_sid;
    }
out:
    return status;
out_free_sid:
    status = GetLastError();
    free(*sid);
    goto out;
}