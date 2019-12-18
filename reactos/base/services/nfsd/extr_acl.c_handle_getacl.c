#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  count; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ nfsacl41 ;
struct TYPE_18__ {int query; int /*<<< orphan*/ * sec_desc; scalar_t__ sec_desc_len; } ;
struct TYPE_13__ {TYPE_6__ getacl; } ;
struct TYPE_15__ {TYPE_4__* state_ref; TYPE_1__ args; } ;
typedef  TYPE_3__ nfs41_upcall ;
struct TYPE_16__ {int /*<<< orphan*/  type; int /*<<< orphan*/  file; int /*<<< orphan*/  session; } ;
typedef  TYPE_4__ nfs41_open_state ;
struct TYPE_17__ {char* owner; char* owner_group; TYPE_2__* acl; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_5__ nfs41_file_info ;
typedef  TYPE_6__ getacl_upcall_args ;
struct TYPE_19__ {int count; int* arr; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_7__ bitmap4 ;
typedef  int /*<<< orphan*/  SECURITY_DESCRIPTOR ;
typedef  int /*<<< orphan*/ * PSID ;
typedef  int /*<<< orphan*/ * PACL ;
typedef  char* LPSTR ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ACLLVL ; 
 int DACL_SECURITY_INFORMATION ; 
 int ERROR_INSUFFICIENT_BUFFER ; 
 int ERROR_INTERNAL_ERROR ; 
 int ERROR_NOT_SUPPORTED ; 
 int ERROR_SUCCESS ; 
 int FATTR4_WORD0_ACL ; 
 int FATTR4_WORD1_OWNER ; 
 int FATTR4_WORD1_OWNER_GROUP ; 
 int GROUP_SECURITY_INFORMATION ; 
 int GetLastError () ; 
 int InitializeSecurityDescriptor (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int MakeSelfRelativeSD (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 int NFS4_OPAQUE_LIMIT ; 
 int OWNER_SECURITY_INFORMATION ; 
 int /*<<< orphan*/  SECURITY_DESCRIPTOR_REVISION ; 
 int SetSecurityDescriptorDacl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int SetSecurityDescriptorGroup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int SetSecurityDescriptorOwner (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int convert_nfs4acl_2_dacl (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ***) ; 
 int /*<<< orphan*/  convert_nfs4name_2_user_domain (char*,char**) ; 
 int /*<<< orphan*/  dprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  eprintf (char*,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_sids (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * malloc (scalar_t__) ; 
 int map_name_2_sid (scalar_t__*,int /*<<< orphan*/ **,char*) ; 
 int nfs41_getattr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_7__*,TYPE_5__*) ; 
 int /*<<< orphan*/  nfsacl41_free (TYPE_2__*) ; 

__attribute__((used)) static int handle_getacl(nfs41_upcall *upcall)
{
    int status = ERROR_NOT_SUPPORTED;
    getacl_upcall_args *args = &upcall->args.getacl;
    nfs41_open_state *state = upcall->state_ref;
    nfs41_file_info info = { 0 };
    bitmap4 attr_request = { 0 };
    LPSTR domain = NULL;
    SECURITY_DESCRIPTOR sec_desc;
    PACL dacl = NULL;
    PSID *sids = NULL;
    PSID osid = NULL, gsid = NULL;
    DWORD sid_len;
    char owner[NFS4_OPAQUE_LIMIT], group[NFS4_OPAQUE_LIMIT];
    nfsacl41 acl = { 0 };

    // need to cache owner/group information XX
    attr_request.count = 2;
    attr_request.arr[1] = FATTR4_WORD1_OWNER | FATTR4_WORD1_OWNER_GROUP;
    if (args->query & DACL_SECURITY_INFORMATION) {
        info.acl = &acl;
        attr_request.arr[0] |= FATTR4_WORD0_ACL;
    }
    info.owner = owner;
    info.owner_group = group;
    status = nfs41_getattr(state->session, &state->file, &attr_request, &info);
    if (status) {
        eprintf("handle_getacl: nfs41_cached_getattr() failed with %d\n", 
                status);
        goto out;
    }

    status = InitializeSecurityDescriptor(&sec_desc, 
                                          SECURITY_DESCRIPTOR_REVISION);
    if (!status) {
        status = GetLastError();
        eprintf("handle_getacl: InitializeSecurityDescriptor failed with %d\n", 
                status);
        goto out;
    }
     /* can't (re)use the same sid variable for both owner and group sids 
      * because security descriptor is created in absolute-form and it just
      * stores pointers to the sids. thus each owner and group needs its own
      * memory. free them after creating self-relative security descriptor. 
      */
    if (args->query & OWNER_SECURITY_INFORMATION) {
        // parse user@domain. currently ignoring domain part XX
        convert_nfs4name_2_user_domain(info.owner, &domain);
        dprintf(ACLLVL, "handle_getacl: OWNER_SECURITY_INFORMATION: for user=%s "
                "domain=%s\n", info.owner, domain?domain:"<null>");
        sid_len = 0;
        status = map_name_2_sid(&sid_len, &osid, info.owner);
        if (status)
            goto out;
        status = SetSecurityDescriptorOwner(&sec_desc, osid, TRUE);
        if (!status) {
            status = GetLastError();
            eprintf("handle_getacl: SetSecurityDescriptorOwner failed with "
                    "%d\n", status);
            goto out;
        }
    }
    if (args->query & GROUP_SECURITY_INFORMATION) {
        convert_nfs4name_2_user_domain(info.owner_group, &domain);
        dprintf(ACLLVL, "handle_getacl: GROUP_SECURITY_INFORMATION: for %s "
                "domain=%s\n", info.owner_group, domain?domain:"<null>");
        sid_len = 0;
        status = map_name_2_sid(&sid_len, &gsid, info.owner_group);
        if (status)
            goto out;
        status = SetSecurityDescriptorGroup(&sec_desc, gsid, TRUE);
        if (!status) {
            status = GetLastError();
            eprintf("handle_getacl: SetSecurityDescriptorGroup failed with "
                    "%d\n", status);
            goto out;
        }
    }
    if (args->query & DACL_SECURITY_INFORMATION) {
        dprintf(ACLLVL, "handle_getacl: DACL_SECURITY_INFORMATION\n");
        status = convert_nfs4acl_2_dacl(info.acl, state->type, &dacl, &sids);
        if (status)
            goto out;
        status = SetSecurityDescriptorDacl(&sec_desc, TRUE, dacl, TRUE);
        if (!status) {
            status = GetLastError();
            eprintf("handle_getacl: SetSecurityDescriptorDacl failed with "
                    "%d\n", status);
            goto out;
        }
    }

    args->sec_desc_len = 0;
    status = MakeSelfRelativeSD(&sec_desc, args->sec_desc, &args->sec_desc_len);
    if (status) {
        status = ERROR_INTERNAL_ERROR;
        goto out;
    }
    status = GetLastError();
    if (status != ERROR_INSUFFICIENT_BUFFER) {
        eprintf("handle_getacl: MakeSelfRelativeSD failes with %d\n", status);
        goto out;
    }
    args->sec_desc = malloc(args->sec_desc_len);
    if (args->sec_desc == NULL) {
        status = GetLastError();
        goto out;
    }
    status = MakeSelfRelativeSD(&sec_desc, args->sec_desc, &args->sec_desc_len);
    if (!status) {
        status = GetLastError();
        eprintf("handle_getacl: MakeSelfRelativeSD failes with %d\n", status);
        free(args->sec_desc);
        goto out;
    } else status = ERROR_SUCCESS;

out:
    if (args->query & OWNER_SECURITY_INFORMATION) {
        if (osid) free(osid);
    }
    if (args->query & GROUP_SECURITY_INFORMATION) {
        if (gsid) free(gsid);
    }
    if (args->query & DACL_SECURITY_INFORMATION) {
        if (sids) free_sids(sids, info.acl->count);
        free(dacl);
        nfsacl41_free(info.acl);
    }
    return status;
}