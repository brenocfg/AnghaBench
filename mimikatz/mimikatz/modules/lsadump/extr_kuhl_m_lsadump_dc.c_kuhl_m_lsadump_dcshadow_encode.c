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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  UNICODE_STRING ;
struct TYPE_10__ {int /*<<< orphan*/  dwFlag; } ;
struct TYPE_8__ {int /*<<< orphan*/  dwFlag; int /*<<< orphan*/  usnTimeChanged; int /*<<< orphan*/  usnOriginating; int /*<<< orphan*/  uidOriginatingDsa; } ;
struct TYPE_9__ {TYPE_1__ MetaData; } ;
typedef  TYPE_2__* PDCSHADOW_PUSH_REQUEST_OBJECT_ATTRIBUTE ;
typedef  TYPE_3__* PDCSHADOW_PUSH_REQUEST_OBJECT ;
typedef  int /*<<< orphan*/  PDCSHADOW_PUSH_REQUEST ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/ * LPCWSTR ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OBJECT_DYNAMIC ; 
 int /*<<< orphan*/  PRINT_ERROR (char*) ; 
 int /*<<< orphan*/  REPLICATION_TIME_SET ; 
 int /*<<< orphan*/  REPLICATION_UID_SET ; 
 int /*<<< orphan*/  REPLICATION_USN_SET ; 
 int /*<<< orphan*/  RtlGUIDFromString (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RtlInitUnicodeString (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kuhl_m_lsadump_dcshadow_clean_push_request (int /*<<< orphan*/ ) ; 
 scalar_t__ kuhl_m_lsadump_dcshadow_encode_add_attribute_if_needed (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__*,TYPE_2__**) ; 
 scalar_t__ kuhl_m_lsadump_dcshadow_encode_add_object_if_needed (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__**) ; 
 scalar_t__ kuhl_m_lsadump_dcshadow_encode_add_value (int /*<<< orphan*/ *,TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  kuhl_m_lsadump_dcshadow_remove_attribute (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kuhl_m_lsadump_dcshadow_remove_object (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ kull_m_string_args_byName (int,int /*<<< orphan*/ **,char*,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 scalar_t__ kull_m_string_stringToFileTime (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wcstoul (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

NTSTATUS kuhl_m_lsadump_dcshadow_encode(PDCSHADOW_PUSH_REQUEST request, int argc, wchar_t * argv[])
{
	LPCWSTR szObject, szAttribute, szValue = NULL, szSid = NULL, szReplOriginatingUid = NULL, szReplOriginatingUsn = NULL, szReplOriginatingTime = NULL;
	PDCSHADOW_PUSH_REQUEST_OBJECT pObject;
	PDCSHADOW_PUSH_REQUEST_OBJECT_ATTRIBUTE pAttribute;
	BOOL cleanData = kull_m_string_args_byName(argc, argv, L"clean", NULL, NULL), multipleValues = kull_m_string_args_byName(argc, argv, L"multiple", NULL, NULL);
	UNICODE_STRING us;

	if(kull_m_string_args_byName(argc, argv, L"object", &szObject, NULL))
	{
		if(kull_m_string_args_byName(argc, argv, L"attribute", &szAttribute, NULL))
		{
			if(kull_m_string_args_byName(argc, argv, L"value", &szValue, NULL))
			{
				if(kuhl_m_lsadump_dcshadow_encode_add_object_if_needed(request, szObject, &pObject))
				{
					if(kuhl_m_lsadump_dcshadow_encode_add_attribute_if_needed(request, szAttribute, pObject, &pAttribute))
					{
						if(kuhl_m_lsadump_dcshadow_encode_add_value(szValue, pAttribute, multipleValues))
						{
							if(kull_m_string_args_byName(argc, argv, L"replOriginatingUid", &szReplOriginatingUid, NULL))
							{
								RtlInitUnicodeString(&us, szReplOriginatingUid);
								if(NT_SUCCESS(RtlGUIDFromString(&us, &(pAttribute->MetaData.uidOriginatingDsa))))
									pAttribute->MetaData.dwFlag |= REPLICATION_UID_SET;
								else PRINT_ERROR(L"unable parse replOriginatingUid\n");
							}
							if(kull_m_string_args_byName(argc, argv, L"replOriginatingUsn", &szReplOriginatingUsn, NULL))
							{
								pAttribute->MetaData.usnOriginating = wcstoul(szReplOriginatingUsn, NULL, 0);
								pAttribute->MetaData.dwFlag |= REPLICATION_USN_SET;
							}
							if(kull_m_string_args_byName(argc, argv, L"replOriginatingTime", &szReplOriginatingTime, NULL))
							{
								if(kull_m_string_stringToFileTime(szReplOriginatingTime, &pAttribute->MetaData.usnTimeChanged))
									pAttribute->MetaData.dwFlag |= REPLICATION_TIME_SET;
								else PRINT_ERROR(L"unable parse replOriginatingTime\n");
							}
							if(kull_m_string_args_byName(argc, argv, L"dynamic", NULL, NULL))
							{
								pObject->dwFlag |= OBJECT_DYNAMIC;
							}
						}
						else PRINT_ERROR(L"unable to set value\n");
					}
					else PRINT_ERROR(L"unable to add attribute\n");
				}
				else PRINT_ERROR(L"unable to add object\n");
			}
			else if(cleanData)
			{
				if(!kuhl_m_lsadump_dcshadow_remove_attribute(request, szObject, szAttribute))
					PRINT_ERROR(L"object or attribute not found\n");
			}
			else PRINT_ERROR(L"value missing\n");
		}
		else if(cleanData)
		{
			if(!kuhl_m_lsadump_dcshadow_remove_object(request, szObject))
				PRINT_ERROR(L"object not found\n");
		}
		else PRINT_ERROR(L"attribute missing\n");
	}
	else
	{
		if(cleanData)
			kuhl_m_lsadump_dcshadow_clean_push_request(request);
		else PRINT_ERROR(L"object missing\n");
	}
	return ERROR_SUCCESS;
}