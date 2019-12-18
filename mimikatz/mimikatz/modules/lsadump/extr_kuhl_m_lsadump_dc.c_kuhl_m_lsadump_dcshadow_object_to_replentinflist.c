#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_34__   TYPE_9__ ;
typedef  struct TYPE_33__   TYPE_8__ ;
typedef  struct TYPE_32__   TYPE_7__ ;
typedef  struct TYPE_31__   TYPE_6__ ;
typedef  struct TYPE_30__   TYPE_5__ ;
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;
typedef  struct TYPE_25__   TYPE_15__ ;
typedef  struct TYPE_24__   TYPE_14__ ;
typedef  struct TYPE_23__   TYPE_13__ ;
typedef  struct TYPE_22__   TYPE_12__ ;
typedef  struct TYPE_21__   TYPE_11__ ;
typedef  struct TYPE_20__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_33__ {int attrCount; TYPE_15__* pAttr; } ;
struct TYPE_34__ {TYPE_8__ AttrBlock; int /*<<< orphan*/  ulFlags; TYPE_14__* pName; } ;
struct TYPE_32__ {int timeChanged; int /*<<< orphan*/  dwVersion; scalar_t__ usnOriginating; int /*<<< orphan*/  uuidDsaOriginating; } ;
struct TYPE_30__ {int dwFlag; int /*<<< orphan*/  curTimeChanged; int /*<<< orphan*/  usnTimeChanged; scalar_t__ usnOriginating; int /*<<< orphan*/  uidOriginatingDsa; int /*<<< orphan*/  curRevision; } ;
struct TYPE_28__ {int /*<<< orphan*/  valCount; int /*<<< orphan*/ * pAVal; } ;
struct TYPE_31__ {TYPE_5__ MetaData; TYPE_3__ AttrVal; TYPE_1__* pAttribute; } ;
struct TYPE_29__ {int /*<<< orphan*/  InstanceId; } ;
struct TYPE_27__ {int /*<<< orphan*/  valCount; int /*<<< orphan*/ * pAVal; } ;
struct TYPE_26__ {int /*<<< orphan*/  Oid; } ;
struct TYPE_25__ {TYPE_2__ AttrVal; int /*<<< orphan*/  attrTyp; } ;
struct TYPE_24__ {int structLen; int NameLen; int SidLen; int /*<<< orphan*/  Guid; int /*<<< orphan*/  Sid; int /*<<< orphan*/ * StringName; } ;
struct TYPE_23__ {scalar_t__ maxDCUsn; TYPE_4__ realDc; int /*<<< orphan*/  szDomainName; } ;
struct TYPE_22__ {int dwFlag; int cbAttributes; TYPE_6__* pAttributes; int /*<<< orphan*/  ParentGuid; int /*<<< orphan*/ * szObjectDN; int /*<<< orphan*/  ObjectGUID; int /*<<< orphan*/  pSid; } ;
struct TYPE_21__ {int cNumProps; TYPE_7__* rgMetaData; } ;
struct TYPE_20__ {int fIsNCPrefix; TYPE_11__* pMetaDataExt; TYPE_9__ Entinf; int /*<<< orphan*/ * pParentGuid; int /*<<< orphan*/ * pNextEntInf; } ;
typedef  int /*<<< orphan*/  SCHEMA_PREFIX_TABLE ;
typedef  TYPE_10__ REPLENTINFLIST ;
typedef  int* PULONGLONG ;
typedef  TYPE_11__ PROPERTY_META_DATA_EXT_VECTOR ;
typedef  int /*<<< orphan*/  PROPERTY_META_DATA_EXT ;
typedef  scalar_t__ PFILETIME ;
typedef  TYPE_12__* PDCSHADOW_PUSH_REQUEST_OBJECT ;
typedef  TYPE_13__* PDCSHADOW_DOMAIN_INFO ;
typedef  int /*<<< orphan*/  GUID ;
typedef  int DWORD ;
typedef  int DSTIME ;
typedef  TYPE_14__ DSNAME ;
typedef  int /*<<< orphan*/  BOOL ;
typedef  TYPE_15__ ATTR ;

/* Variables and functions */
 int /*<<< orphan*/  ENTINF_DYNAMIC_OBJECT ; 
 int /*<<< orphan*/  ENTINF_FROM_MASTER ; 
 int /*<<< orphan*/  FALSE ; 
 int GetLengthSid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IsNullGuid (int /*<<< orphan*/ *) ; 
 scalar_t__ IsValidSid (int /*<<< orphan*/ *) ; 
 scalar_t__ MIDL_user_allocate (int) ; 
 int OBJECT_DYNAMIC ; 
 int REPLICATION_TIME_SET ; 
 int REPLICATION_UID_SET ; 
 int REPLICATION_USN_SET ; 
 int /*<<< orphan*/  RtlCopyMemory (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  RtlZeroMemory (TYPE_14__*,int) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ _wcsicmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kull_m_rpc_drsr_MakeAttid (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int lstrlen (int /*<<< orphan*/ *) ; 

BOOL kuhl_m_lsadump_dcshadow_object_to_replentinflist(PDCSHADOW_DOMAIN_INFO info, REPLENTINFLIST ** ppReplEnt, PDCSHADOW_PUSH_REQUEST_OBJECT object, SCHEMA_PREFIX_TABLE *pPrefixTableSrc, PFILETIME pCurrentFt)
{
	DWORD i, len;
	
	if(*ppReplEnt = (REPLENTINFLIST *) MIDL_user_allocate(sizeof(REPLENTINFLIST)))
	{
		(*ppReplEnt)->pNextEntInf = NULL;
		len = lstrlen(object->szObjectDN);
		if((*ppReplEnt)->Entinf.pName = (DSNAME *) MIDL_user_allocate(sizeof(DSNAME) + len * sizeof(WCHAR)))
		{
			RtlZeroMemory((*ppReplEnt)->Entinf.pName, sizeof(DSNAME));
			(*ppReplEnt)->Entinf.pName->structLen = sizeof(DSNAME) + len * sizeof(WCHAR);
			(*ppReplEnt)->Entinf.pName->NameLen = len;
			RtlCopyMemory((*ppReplEnt)->Entinf.pName->StringName, object->szObjectDN, (len+1)*sizeof(WCHAR));
			if(IsValidSid(&object->pSid))
			{
				(*ppReplEnt)->Entinf.pName->SidLen = GetLengthSid(&object->pSid);
				RtlCopyMemory(&(*ppReplEnt)->Entinf.pName->Sid, &object->pSid, (*ppReplEnt)->Entinf.pName->SidLen);
			}
			RtlCopyMemory(&(*ppReplEnt)->Entinf.pName->Guid, &object->ObjectGUID, sizeof(GUID));
		}
		(*ppReplEnt)->Entinf.ulFlags = ENTINF_FROM_MASTER;
		if (OBJECT_DYNAMIC & object->dwFlag)
			(*ppReplEnt)->Entinf.ulFlags |= ENTINF_DYNAMIC_OBJECT;
		(*ppReplEnt)->Entinf.AttrBlock.attrCount =  object->cbAttributes;
		(*ppReplEnt)->fIsNCPrefix = (_wcsicmp(info->szDomainName, object->szObjectDN) == 0);
		(*ppReplEnt)->pParentGuid = NULL;
		if (!IsNullGuid(&object->ParentGuid) && ((*ppReplEnt)->pParentGuid = (GUID*) MIDL_user_allocate(sizeof(GUID))) != NULL)
		{
			RtlCopyMemory((*ppReplEnt)->pParentGuid, &object->ParentGuid, sizeof(GUID));
		}
		if((*ppReplEnt)->Entinf.AttrBlock.pAttr = (ATTR *) MIDL_user_allocate(sizeof(ATTR) * (*ppReplEnt)->Entinf.AttrBlock.attrCount))
		{
			for(i = 0; i < (*ppReplEnt)->Entinf.AttrBlock.attrCount; i++)
			{
				kull_m_rpc_drsr_MakeAttid(pPrefixTableSrc, object->pAttributes[i].pAttribute->Oid, &(*ppReplEnt)->Entinf.AttrBlock.pAttr[i].attrTyp, TRUE);
				
				(*ppReplEnt)->Entinf.AttrBlock.pAttr[i].AttrVal.pAVal =  object->pAttributes[i].AttrVal.pAVal;
				object->pAttributes[i].AttrVal.pAVal = NULL;
				(*ppReplEnt)->Entinf.AttrBlock.pAttr[i].AttrVal.valCount = object->pAttributes[i].AttrVal.valCount;
			}
		}
		else return FALSE;
		if((*ppReplEnt)->pMetaDataExt = (PROPERTY_META_DATA_EXT_VECTOR *) MIDL_user_allocate(sizeof(PROPERTY_META_DATA_EXT_VECTOR) + (((*ppReplEnt)->Entinf.AttrBlock.attrCount - 1 ) * sizeof(PROPERTY_META_DATA_EXT))))
		{
			(*ppReplEnt)->pMetaDataExt->cNumProps = (*ppReplEnt)->Entinf.AttrBlock.attrCount;
			for(i = 0; i < (*ppReplEnt)->pMetaDataExt->cNumProps; i++)
			{
				(*ppReplEnt)->pMetaDataExt->rgMetaData[i].dwVersion = object->pAttributes[i].MetaData.curRevision;
				if(object->pAttributes[i].MetaData.dwFlag & REPLICATION_UID_SET)
					RtlCopyMemory(&(*ppReplEnt)->pMetaDataExt->rgMetaData[i].uuidDsaOriginating, &object->pAttributes[i].MetaData.uidOriginatingDsa, sizeof(GUID));
				else
					RtlCopyMemory(&(*ppReplEnt)->pMetaDataExt->rgMetaData[i].uuidDsaOriginating, &info->realDc.InstanceId, sizeof(GUID));
				if(object->pAttributes[i].MetaData.dwFlag & REPLICATION_USN_SET)
					(*ppReplEnt)->pMetaDataExt->rgMetaData[i].usnOriginating = object->pAttributes[i].MetaData.usnOriginating;
				else
					(*ppReplEnt)->pMetaDataExt->rgMetaData[i].usnOriginating = ++info->maxDCUsn;
				if(object->pAttributes[i].MetaData.dwFlag & REPLICATION_TIME_SET)
					(*ppReplEnt)->pMetaDataExt->rgMetaData[i].timeChanged = (*(PULONGLONG) &object->pAttributes[i].MetaData.usnTimeChanged) / 10000000;
				else
					(*ppReplEnt)->pMetaDataExt->rgMetaData[i].timeChanged = (*(PULONGLONG) pCurrentFt) / 10000000;
				if (!(*ppReplEnt)->pMetaDataExt->rgMetaData[i].dwVersion || 
					(*ppReplEnt)->pMetaDataExt->rgMetaData[i].timeChanged <= (DSTIME) (*(PULONGLONG) &object->pAttributes[i].MetaData.curTimeChanged) / 10000000)
					(*ppReplEnt)->pMetaDataExt->rgMetaData[i].dwVersion++;
			}
		}
		else return FALSE;
		return TRUE;
	}
	return FALSE;
}