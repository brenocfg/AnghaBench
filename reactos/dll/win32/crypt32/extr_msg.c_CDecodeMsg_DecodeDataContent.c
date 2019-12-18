#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  properties; } ;
struct TYPE_9__ {int /*<<< orphan*/  cbData; int /*<<< orphan*/  pbData; } ;
struct TYPE_8__ {int /*<<< orphan*/  cbData; int /*<<< orphan*/  pbData; } ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  TYPE_1__ CRYPT_DER_BLOB ;
typedef  TYPE_2__ CRYPT_DATA_BLOB ;
typedef  TYPE_3__ CDecodeMsg ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CMSG_CONTENT_PARAM ; 
 int /*<<< orphan*/  CRYPT_DECODE_ALLOC_FLAG ; 
 scalar_t__ ContextPropertyList_SetProperty (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ CryptDecodeObjectEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LocalFree (TYPE_2__*) ; 
 int /*<<< orphan*/  X509_ASN_ENCODING ; 
 int /*<<< orphan*/  X509_OCTET_STRING ; 

__attribute__((used)) static BOOL CDecodeMsg_DecodeDataContent(CDecodeMsg *msg, const CRYPT_DER_BLOB *blob)
{
    BOOL ret;
    CRYPT_DATA_BLOB *data;
    DWORD size;

    ret = CryptDecodeObjectEx(X509_ASN_ENCODING, X509_OCTET_STRING,
     blob->pbData, blob->cbData, CRYPT_DECODE_ALLOC_FLAG, NULL, &data, &size);
    if (ret)
    {
        ret = ContextPropertyList_SetProperty(msg->properties,
         CMSG_CONTENT_PARAM, data->pbData, data->cbData);
        LocalFree(data);
    }
    return ret;
}