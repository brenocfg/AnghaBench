#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  time_t ;
typedef  int /*<<< orphan*/  t ;
struct TYPE_14__ {int /*<<< orphan*/  encrypt_id; } ;
struct TYPE_13__ {int /*<<< orphan*/  attr; } ;
struct TYPE_12__ {TYPE_1__* entries; } ;
struct TYPE_11__ {int /*<<< orphan*/  count; } ;
typedef  TYPE_2__* HPDF_Xref ;
typedef  int /*<<< orphan*/  HPDF_UINT32 ;
typedef  int HPDF_UINT ;
typedef  int /*<<< orphan*/  HPDF_MD5_CTX ;
typedef  TYPE_3__* HPDF_EncryptDict ;
typedef  TYPE_4__* HPDF_Encrypt ;
typedef  TYPE_2__* HPDF_Dict ;
typedef  int /*<<< orphan*/  const HPDF_BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  HPDF_INFO_AUTHOR ; 
 int /*<<< orphan*/  HPDF_INFO_CREATOR ; 
 int /*<<< orphan*/  HPDF_INFO_KEYWORDS ; 
 int /*<<< orphan*/  HPDF_INFO_PRODUCER ; 
 int /*<<< orphan*/  HPDF_INFO_SUBJECT ; 
 int /*<<< orphan*/  HPDF_INFO_TITLE ; 
 char* HPDF_Info_GetInfoAttr (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_MD5Final (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HPDF_MD5Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HPDF_MD5Update (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int HPDF_StrLen (char const*,int) ; 
 int /*<<< orphan*/  HPDF_TIME (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HPDF_UNUSED (TYPE_2__*) ; 

void
HPDF_EncryptDict_CreateID  (HPDF_EncryptDict  dict,
                            HPDF_Dict         info,
                            HPDF_Xref         xref)
{
    HPDF_MD5_CTX ctx;
    HPDF_Encrypt attr = (HPDF_Encrypt)dict->attr;

    /* use the result of 'time' function to get random value.
     * when debugging, 'time' value is ignored.
     */
#ifndef LIBHPDF_DEBUG
    time_t t = HPDF_TIME (NULL);
#endif /* LIBHPDF_DEBUG */

    HPDF_MD5Init (&ctx);
    HPDF_UNUSED (xref);
    HPDF_UNUSED (info);

#ifndef LIBHPDF_DEBUG
    HPDF_MD5Update(&ctx, (HPDF_BYTE *)&t, sizeof(t));

    /* create File Identifier from elements of Into dictionary. */
    if (info) {
        const char *s;
        HPDF_UINT len;

        /* Author */
        s = HPDF_Info_GetInfoAttr (info, HPDF_INFO_AUTHOR);
        if ((len = HPDF_StrLen (s, -1)) > 0)
            HPDF_MD5Update(&ctx, (const HPDF_BYTE *)s, len);

        /* Creator */
        s = HPDF_Info_GetInfoAttr (info, HPDF_INFO_CREATOR);
        if ((len = HPDF_StrLen (s, -1)) > 0)
            HPDF_MD5Update(&ctx, (const HPDF_BYTE *)s, len);

        /* Producer */
        s = HPDF_Info_GetInfoAttr (info, HPDF_INFO_PRODUCER);
        if ((len = HPDF_StrLen (s, -1)) > 0)
            HPDF_MD5Update(&ctx, (const HPDF_BYTE *)s, len);

        /* Title */
        s = HPDF_Info_GetInfoAttr (info, HPDF_INFO_TITLE);
        if ((len = HPDF_StrLen (s, -1)) > 0)
            HPDF_MD5Update(&ctx, (const HPDF_BYTE *)s, len);

        /* Subject */
        s = HPDF_Info_GetInfoAttr (info, HPDF_INFO_SUBJECT);
        if ((len = HPDF_StrLen (s, -1)) > 0)
            HPDF_MD5Update(&ctx, (const HPDF_BYTE *)s, len);

        /* Keywords */
        s = HPDF_Info_GetInfoAttr (info, HPDF_INFO_KEYWORDS);
        if ((len = HPDF_StrLen (s, -1)) > 0)
            HPDF_MD5Update(&ctx, (const HPDF_BYTE *)s, len);

        HPDF_MD5Update(&ctx, (const HPDF_BYTE *)&(xref->entries->count),
                sizeof(HPDF_UINT32));

    }
#endif
    HPDF_MD5Final(attr->encrypt_id, &ctx);
}