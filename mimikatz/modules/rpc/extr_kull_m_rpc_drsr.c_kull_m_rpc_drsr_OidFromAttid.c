#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ USHORT ;
struct TYPE_10__ {int length; int /*<<< orphan*/  elements; } ;
struct TYPE_9__ {void** value; scalar_t__ length; } ;
struct TYPE_8__ {size_t PrefixCount; TYPE_1__* pPrefixEntry; } ;
struct TYPE_7__ {scalar_t__ ndx; TYPE_4__ prefix; } ;
typedef  TYPE_2__ SCHEMA_PREFIX_TABLE ;
typedef  void** PBYTE ;
typedef  TYPE_3__ OssEncodedOID ;
typedef  TYPE_4__ OID_t ;
typedef  int /*<<< orphan*/ * LPSTR ;
typedef  size_t DWORD ;
typedef  void* BYTE ;
typedef  int ATTRTYP ;

/* Variables and functions */
 int /*<<< orphan*/  LPTR ; 
 scalar_t__ LocalAlloc (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  LocalFree (void**) ; 
 int /*<<< orphan*/  RtlCopyMemory (void**,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kull_m_asn1_Eoid2DotVal (TYPE_3__*,int /*<<< orphan*/ **) ; 

LPSTR kull_m_rpc_drsr_OidFromAttid(SCHEMA_PREFIX_TABLE *prefixTable, ATTRTYP type)
{
	LPSTR szOid = NULL;
	DWORD i;
	USHORT low = (USHORT) type, idx = (USHORT) (type >> 16);
	OID_t *pLittleOid = NULL;
	OssEncodedOID encodedOid;

	for(i = 0; i < prefixTable->PrefixCount; i++)
	{
		if(prefixTable->pPrefixEntry[i].ndx == idx)
		{
			pLittleOid = &prefixTable->pPrefixEntry[i].prefix;
			break;
		}
	}
	if(pLittleOid)
	{
		encodedOid.length = (USHORT) (pLittleOid->length + ((low < 0x80) ? 1 : 2));
		if(encodedOid.value = (PBYTE) LocalAlloc(LPTR, encodedOid.length))
		{
			RtlCopyMemory(encodedOid.value, pLittleOid->elements, pLittleOid->length);
			if(low < 0x80)
				encodedOid.value[pLittleOid->length] = (BYTE) low;
			else
			{
				if(low >= 0x8000)
					low -= 0x8000;
				encodedOid.value[pLittleOid->length] = (BYTE) (((low / 0x80) % 0x80) + 0x80);
				encodedOid.value[pLittleOid->length + 1] = (BYTE) (low % 0x80);
			}
			if(!kull_m_asn1_Eoid2DotVal(&encodedOid, &szOid))
				szOid = NULL;
			LocalFree(encodedOid.value);
		}
	}
	return szOid;
}