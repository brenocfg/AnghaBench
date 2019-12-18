#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int Length; int /*<<< orphan*/  Buffer; } ;
typedef  TYPE_2__ UNICODE_STRING ;
typedef  int ULONG ;
struct TYPE_17__ {int Length; int /*<<< orphan*/  Buffer; } ;
struct TYPE_20__ {int HandleCount; TYPE_1__ Name; TYPE_3__* Handles; } ;
struct TYPE_19__ {int ProcessId; int ObjectTypeNumber; int /*<<< orphan*/  Handle; } ;
typedef  TYPE_3__ SYSTEM_HANDLE ;
typedef  int /*<<< orphan*/  RList ;
typedef  int /*<<< orphan*/  RDebugDesc ;
typedef  TYPE_4__* PVOID ;
typedef  TYPE_2__* PUNICODE_STRING ;
typedef  TYPE_4__* PSYSTEM_HANDLE_INFORMATION ;
typedef  TYPE_4__* POBJECT_TYPE_INFORMATION ;
typedef  scalar_t__ NTSTATUS ;
typedef  TYPE_4__* LPVOID ;
typedef  int /*<<< orphan*/ * HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetCurrentProcess () ; 
 int /*<<< orphan*/  PROCESS_DUP_HANDLE ; 
 scalar_t__ STATUS_INFO_LENGTH_MISMATCH ; 
 int /*<<< orphan*/  SystemHandleInformation ; 
 int /*<<< orphan*/  free (TYPE_4__*) ; 
 TYPE_4__* malloc (size_t) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/ * r_debug_desc_new (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ,char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_list_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * r_list_newf (int /*<<< orphan*/  (*) (TYPE_4__*)) ; 
 int /*<<< orphan*/  r_sys_perror (char*) ; 
 void* realloc (TYPE_4__*,int) ; 
 scalar_t__ w32_NtDuplicateObject (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ w32_NtQueryObject (int /*<<< orphan*/ *,int,TYPE_4__*,int,int*) ; 
 scalar_t__ w32_NtQuerySystemInformation (int /*<<< orphan*/ ,TYPE_4__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * w32_OpenProcess (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wcstombs (TYPE_4__*,int /*<<< orphan*/ ,int) ; 

RList *w32_desc_list(int pid) {
	RDebugDesc *desc;
	RList *ret = r_list_newf (free);
	int i;
	HANDLE ph;
	PSYSTEM_HANDLE_INFORMATION handleInfo;
	NTSTATUS status;
	ULONG handleInfoSize = 0x10000;
	LPVOID buff;
	if (!ret) {
		perror ("win_desc_list/r_list_new");
		return NULL;
	}
	if (!(ph = w32_OpenProcess (PROCESS_DUP_HANDLE, FALSE, pid))) {
		r_sys_perror ("win_desc_list/OpenProcess");
		r_list_free (ret);
		return NULL;
	}
	handleInfo = (PSYSTEM_HANDLE_INFORMATION)malloc (handleInfoSize);
	#define STATUS_INFO_LENGTH_MISMATCH 0xc0000004
	#define SystemHandleInformation 16
	while ((status = w32_NtQuerySystemInformation (SystemHandleInformation, handleInfo, handleInfoSize, NULL)) == STATUS_INFO_LENGTH_MISMATCH) {
		handleInfoSize *= 2;
		void *tmp = realloc (handleInfo, (size_t)handleInfoSize);
		if (tmp) {
			handleInfo = (PSYSTEM_HANDLE_INFORMATION)tmp;
		}
	}
	if (status) {
		r_sys_perror ("win_desc_list/NtQuerySystemInformation");
		CloseHandle (ph);
		r_list_free (ret);
		return NULL;
	}
	for (i = 0; i < handleInfo->HandleCount; i++) {
		SYSTEM_HANDLE handle = handleInfo->Handles[i];
		HANDLE dupHandle = NULL;
		POBJECT_TYPE_INFORMATION objectTypeInfo;
		PVOID objectNameInfo;
		UNICODE_STRING objectName;
		ULONG returnLength;
		if (handle.ProcessId != pid) {
			continue;
		}
		if (handle.ObjectTypeNumber != 0x1c) {
			continue;
		}
		if (w32_NtDuplicateObject (ph, &handle.Handle, GetCurrentProcess (), &dupHandle, 0, 0, 0)) {
			continue;
		}
		objectTypeInfo = (POBJECT_TYPE_INFORMATION)malloc (0x1000);
		if (w32_NtQueryObject (dupHandle, 2, objectTypeInfo, 0x1000, NULL)) {
			CloseHandle (dupHandle);
			continue;
		}
		objectNameInfo = malloc (0x1000);
		if (!objectNameInfo) {
			break;
		}
		if (w32_NtQueryObject (dupHandle, 1, objectNameInfo, 0x1000, &returnLength)) {
			void *tmp = realloc (objectNameInfo, returnLength);
			if (tmp) {
				objectNameInfo = tmp;
			}
			if (w32_NtQueryObject (dupHandle, 1, objectNameInfo, returnLength, NULL)) {
				free (objectTypeInfo);
				free (objectNameInfo);
				CloseHandle (dupHandle);
				continue;
			}
		}
		objectName = *(PUNICODE_STRING)objectNameInfo;
		if (objectName.Length) {
			//objectTypeInfo->Name.Length ,objectTypeInfo->Name.Buffer, objectName.Length / 2, objectName.Buffer
			buff = malloc ((size_t)(objectName.Length / 2) + 1);
			wcstombs (buff, objectName.Buffer, objectName.Length / 2);
			desc = r_debug_desc_new (handle.Handle, buff, 0, '?', 0);
			if (!desc) {
				free (buff);
				break;
			}
			r_list_append (ret, desc);
			free (buff);
		} else {
			buff = malloc ((size_t)(objectTypeInfo->Name.Length / 2) + 1);
			wcstombs (buff, objectTypeInfo->Name.Buffer, objectTypeInfo->Name.Length);
			desc = r_debug_desc_new (handle.Handle, buff, 0, '?', 0);
			if (!desc) {
				free (buff);
				break;
			}
			r_list_append (ret, desc);
			free (buff);
		}
		free (objectTypeInfo);
		free (objectNameInfo);
		CloseHandle (dupHandle);
	}
	free (handleInfo);
	CloseHandle (ph);
	return ret;
}