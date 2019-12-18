#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int Size; int VendorID; int ProductID; } ;
struct TYPE_12__ {int cbSize; scalar_t__ hDevice; struct TYPE_12__* next; int /*<<< orphan*/  DevicePath; scalar_t__ id; TYPE_4__ hidAttributes; int /*<<< orphan*/  hidCaps; } ;
struct TYPE_11__ {int cbSize; } ;
typedef  int /*<<< orphan*/  SR98_DEVICE ;
typedef  int /*<<< orphan*/  SP_DEVICE_INTERFACE_DETAIL_DATA ;
typedef  TYPE_1__ SP_DEVICE_INTERFACE_DATA ;
typedef  TYPE_2__* PSR98_DEVICE ;
typedef  TYPE_2__* PSP_DEVICE_INTERFACE_DETAIL_DATA ;
typedef  int /*<<< orphan*/  PHIDP_PREPARSED_DATA ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  TYPE_4__ HIDD_ATTRIBUTES ;
typedef  scalar_t__ HDEVINFO ;
typedef  scalar_t__ HANDLE ;
typedef  int /*<<< orphan*/  GUID ;
typedef  scalar_t__ DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 void* CreateFile (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int DIGCF_DEVICEINTERFACE ; 
 int DIGCF_PRESENT ; 
 scalar_t__ ERROR_INSUFFICIENT_BUFFER ; 
 int FILE_READ_DATA ; 
 int FILE_SHARE_READ ; 
 int FILE_SHARE_WRITE ; 
 int FILE_WRITE_DATA ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  HidD_FreePreparsedData (int /*<<< orphan*/ ) ; 
 scalar_t__ HidD_GetAttributes (scalar_t__,TYPE_4__*) ; 
 int /*<<< orphan*/  HidD_GetHidGuid (int /*<<< orphan*/ *) ; 
 scalar_t__ HidD_GetPreparsedData (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HidP_GetCaps (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  LPTR ; 
 scalar_t__ LocalAlloc (int /*<<< orphan*/ ,int) ; 
 scalar_t__ LocalFree (TYPE_2__*) ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 int /*<<< orphan*/  PRINT_ERROR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRINT_ERROR_AUTO (char*) ; 
 int /*<<< orphan*/  SetupDiDestroyDeviceInfoList (scalar_t__) ; 
 int SetupDiEnumDeviceInterfaces (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,TYPE_1__*) ; 
 scalar_t__ SetupDiGetClassDevs (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ SetupDiGetDeviceInterfaceDetail (scalar_t__,TYPE_1__*,TYPE_2__*,scalar_t__,scalar_t__*,int /*<<< orphan*/ *) ; 
 int TRUE ; 
 int /*<<< orphan*/  _wcsdup (int /*<<< orphan*/ ) ; 

BOOL sr98_devices_get(PSR98_DEVICE *devices, DWORD *count)
{
	PSR98_DEVICE *next = devices;
	GUID guidHid;
	HDEVINFO hDevInfo;
	SP_DEVICE_INTERFACE_DATA DeviceInterfaceData;
	BOOL enumStatus;
	DWORD enumIndex, dwRequired, id = 0;
	PSP_DEVICE_INTERFACE_DETAIL_DATA DeviceInterfaceDetailData;
	HANDLE deviceHandle;
	HIDD_ATTRIBUTES attributes;
	PHIDP_PREPARSED_DATA PreparsedData;
	NTSTATUS status;

	*next = NULL;
	HidD_GetHidGuid(&guidHid);
	hDevInfo = SetupDiGetClassDevs(&guidHid, NULL, NULL, DIGCF_DEVICEINTERFACE | DIGCF_PRESENT);
	if(hDevInfo != INVALID_HANDLE_VALUE)
	{
		for(enumIndex = 0, enumStatus = TRUE; enumStatus; enumIndex++)
		{
			DeviceInterfaceData.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);
			if(enumStatus = SetupDiEnumDeviceInterfaces(hDevInfo, NULL, &guidHid, enumIndex, &DeviceInterfaceData))
			{
				dwRequired = 0;
				if(!SetupDiGetDeviceInterfaceDetail(hDevInfo, &DeviceInterfaceData, NULL, 0, &dwRequired, NULL) && (GetLastError() == ERROR_INSUFFICIENT_BUFFER))
				{
					if(DeviceInterfaceDetailData = (PSP_DEVICE_INTERFACE_DETAIL_DATA) LocalAlloc(LPTR, dwRequired))
					{
						DeviceInterfaceDetailData->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);
						if(SetupDiGetDeviceInterfaceDetail(hDevInfo, &DeviceInterfaceData, DeviceInterfaceDetailData, dwRequired, &dwRequired, NULL))
						{
							deviceHandle = CreateFile(DeviceInterfaceDetailData->DevicePath, 0, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
							if(deviceHandle != INVALID_HANDLE_VALUE)
							{
								attributes.Size = sizeof(HIDD_ATTRIBUTES);
								if(HidD_GetAttributes(deviceHandle, &attributes))
								{
									if((attributes.VendorID == 0x6688) && ((attributes.ProductID >= 0x6850) && (attributes.ProductID <= 0x6868)))
									{
										if(*next = (PSR98_DEVICE) LocalAlloc(LPTR, sizeof(SR98_DEVICE)))
										{
											if(HidD_GetPreparsedData(deviceHandle, &PreparsedData))
											{
												status = HidP_GetCaps(PreparsedData, &(*next)->hidCaps);
												if(!NT_SUCCESS(status))
													PRINT_ERROR(L"HidP_GetCaps (%08x)\n", status);
												HidD_FreePreparsedData(PreparsedData);
											}
											(*next)->DevicePath = _wcsdup(DeviceInterfaceDetailData->DevicePath);
											(*next)->hidAttributes = attributes;
											(*next)->id = id;
											(*next)->hDevice = CreateFile(DeviceInterfaceDetailData->DevicePath, FILE_READ_DATA | FILE_WRITE_DATA, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);

											if((*next)->hDevice && ((*next)->hDevice != INVALID_HANDLE_VALUE))
											{
												next = &(*next)->next;
												id++;
											}
											else
											{
												PRINT_ERROR_AUTO(L"CreateFile (hDevice)");
												*next = (PSR98_DEVICE) LocalFree(*next);
											}
										}
									}
								}
								CloseHandle(deviceHandle);
							}
							else PRINT_ERROR_AUTO(L"CreateFile (deviceHandle)");
						}
						LocalFree(DeviceInterfaceDetailData);
					}
				}
			}
		}
		SetupDiDestroyDeviceInfoList(hDevInfo);
	}
	else PRINT_ERROR_AUTO(L"SetupDiGetClassDevs");

	if(count)
		*count = id;
	return (id > 0);
}