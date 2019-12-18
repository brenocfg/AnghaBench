#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  pbData; int /*<<< orphan*/  cbData; } ;
struct TYPE_7__ {int /*<<< orphan*/  Algid; } ;
struct TYPE_10__ {int cbSize; int /*<<< orphan*/  pwszCNGExtraAlgid; int /*<<< orphan*/  pwszCNGAlgid; TYPE_2__ ExtraInfo; TYPE_1__ u; int /*<<< orphan*/  dwGroupId; scalar_t__* pwszName; int /*<<< orphan*/  pszOID; } ;
struct OIDInfo {int /*<<< orphan*/  entry; TYPE_4__ info; } ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  UINT_PTR ;
struct TYPE_11__ {int /*<<< orphan*/  pwszCNGExtraAlgid; int /*<<< orphan*/  pwszCNGAlgid; TYPE_3__* blob; int /*<<< orphan*/  Algid; int /*<<< orphan*/  dwGroupId; int /*<<< orphan*/  pszOID; scalar_t__* pwszName; } ;
struct TYPE_9__ {int /*<<< orphan*/  pbData; int /*<<< orphan*/  cbData; } ;
typedef  scalar_t__* LPWSTR ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  size_t DWORD ;
typedef  int /*<<< orphan*/  CRYPT_OID_INFO ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_5__*) ; 
 struct OIDInfo* CryptMemAlloc (int) ; 
 int /*<<< orphan*/  IS_INTRESOURCE (scalar_t__*) ; 
 int LoadStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hInstance ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (struct OIDInfo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct OIDInfo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  oidInfo ; 
 TYPE_5__* oidInfoConstructors ; 
 int /*<<< orphan*/  oid_init_localizednames () ; 

__attribute__((used)) static void init_oid_info(void)
{
    DWORD i;

    oid_init_localizednames();
    for (i = 0; i < ARRAY_SIZE(oidInfoConstructors); i++)
    {
        if (!IS_INTRESOURCE(oidInfoConstructors[i].pwszName))
        {
            struct OIDInfo *info;

            /* The name is a static string, so just use the same pointer */
            info = CryptMemAlloc(sizeof(struct OIDInfo));
            if (info)
            {
                memset(info, 0, sizeof(*info));
                info->info.cbSize = sizeof(CRYPT_OID_INFO);
                info->info.pszOID = oidInfoConstructors[i].pszOID;
                info->info.pwszName = oidInfoConstructors[i].pwszName;
                info->info.dwGroupId = oidInfoConstructors[i].dwGroupId;
                info->info.u.Algid = oidInfoConstructors[i].Algid;
                if (oidInfoConstructors[i].blob)
                {
                    info->info.ExtraInfo.cbData =
                     oidInfoConstructors[i].blob->cbData;
                    info->info.ExtraInfo.pbData =
                     oidInfoConstructors[i].blob->pbData;
                }
                info->info.pwszCNGAlgid = oidInfoConstructors[i].pwszCNGAlgid;
                info->info.pwszCNGExtraAlgid = oidInfoConstructors[i].pwszCNGExtraAlgid;
                list_add_tail(&oidInfo, &info->entry);
            }
        }
        else
        {
            LPCWSTR stringresource;
            int len = LoadStringW(hInstance,
             (UINT_PTR)oidInfoConstructors[i].pwszName,
             (LPWSTR)&stringresource, 0);

            if (len)
            {
                struct OIDInfo *info = CryptMemAlloc(sizeof(struct OIDInfo) +
                 (len + 1) * sizeof(WCHAR));

                if (info)
                {
                    memset(info, 0, sizeof(*info));
                    info->info.cbSize = sizeof(CRYPT_OID_INFO);
                    info->info.pszOID = oidInfoConstructors[i].pszOID;
                    info->info.pwszName = (LPWSTR)(info + 1);
                    info->info.dwGroupId = oidInfoConstructors[i].dwGroupId;
                    info->info.u.Algid = oidInfoConstructors[i].Algid;
                    memcpy(info + 1, stringresource, len*sizeof(WCHAR));
                    ((LPWSTR)(info + 1))[len] = 0;
                    if (oidInfoConstructors[i].blob)
                    {
                        info->info.ExtraInfo.cbData =
                         oidInfoConstructors[i].blob->cbData;
                        info->info.ExtraInfo.pbData =
                         oidInfoConstructors[i].blob->pbData;
                    }
                    info->info.pwszCNGAlgid = oidInfoConstructors[i].pwszCNGAlgid;
                    info->info.pwszCNGExtraAlgid = oidInfoConstructors[i].pwszCNGExtraAlgid;
                    list_add_tail(&oidInfo, &info->entry);
                }
            }
        }
    }
}