#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_36__   TYPE_9__ ;
typedef  struct TYPE_35__   TYPE_8__ ;
typedef  struct TYPE_34__   TYPE_7__ ;
typedef  struct TYPE_33__   TYPE_6__ ;
typedef  struct TYPE_32__   TYPE_5__ ;
typedef  struct TYPE_31__   TYPE_4__ ;
typedef  struct TYPE_30__   TYPE_3__ ;
typedef  struct TYPE_29__   TYPE_2__ ;
typedef  struct TYPE_28__   TYPE_1__ ;
typedef  struct TYPE_27__   TYPE_13__ ;
typedef  struct TYPE_26__   TYPE_12__ ;
typedef  struct TYPE_25__   TYPE_11__ ;
typedef  struct TYPE_24__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  WAVEFORMATEX ;
typedef  int /*<<< orphan*/  VOID ;
typedef  int UINT ;
struct TYPE_36__ {int cbSize; int /*<<< orphan*/ * DevicePath; } ;
struct TYPE_35__ {int cbSize; scalar_t__ Reserved; } ;
struct TYPE_34__ {int cbSize; scalar_t__ Reserved; } ;
struct TYPE_33__ {int FormatSize; int SampleSize; int /*<<< orphan*/  Specifier; int /*<<< orphan*/  SubFormat; int /*<<< orphan*/  MajorFormat; scalar_t__ Reserved; int /*<<< orphan*/  Flags; } ;
struct TYPE_32__ {int nChannels; int nSamplesPerSec; int nBlockAlign; int nAvgBytesPerSec; int wBitsPerSample; scalar_t__ cbSize; int /*<<< orphan*/  wFormatTag; } ;
struct TYPE_31__ {int PrioritySubClass; int /*<<< orphan*/  PriorityClass; } ;
struct TYPE_30__ {scalar_t__ Flags; int /*<<< orphan*/  Id; int /*<<< orphan*/  Set; } ;
struct TYPE_29__ {scalar_t__ Flags; int /*<<< orphan*/  Id; int /*<<< orphan*/  Set; } ;
struct TYPE_28__ {int Numerator; int Denominator; } ;
struct TYPE_27__ {TYPE_6__ DataFormat; TYPE_5__ WaveFormatEx; } ;
struct TYPE_26__ {TYPE_4__ Priority; int /*<<< orphan*/ * PinToHandle; scalar_t__ PinId; TYPE_3__ Medium; TYPE_2__ Interface; } ;
struct TYPE_25__ {int /*<<< orphan*/  Flags; int /*<<< orphan*/  Id; int /*<<< orphan*/  Set; } ;
struct TYPE_24__ {int* Data; int FrameExtent; int DataUsed; int Size; TYPE_1__ PresentationTime; } ;
typedef  int /*<<< orphan*/  State ;
typedef  TYPE_7__ SP_DEVINFO_DATA ;
typedef  int /*<<< orphan*/  SP_DEVICE_INTERFACE_DETAIL_DATA ;
typedef  TYPE_8__ SP_DEVICE_INTERFACE_DATA ;
typedef  TYPE_9__* PSP_DEVICE_INTERFACE_DETAIL_DATA ;
typedef  int* PSHORT ;
typedef  TYPE_10__* PKSSTREAM_HEADER ;
typedef  TYPE_11__* PKSPROPERTY ;
typedef  TYPE_12__* PKSPIN_CONNECT ;
typedef  TYPE_13__* PKSDATAFORMAT_WAVEFORMATEX ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  char* LPWSTR ;
typedef  int /*<<< orphan*/  KSSTREAM_HEADER ;
typedef  TYPE_10__ KSSTATE ;
typedef  int /*<<< orphan*/  KSPROPERTY ;
typedef  int /*<<< orphan*/  KSPIN_CONNECT ;
typedef  int /*<<< orphan*/  KSDATAFORMAT_WAVEFORMATEX ;
typedef  int /*<<< orphan*/  KSDATAFORMAT ;
typedef  int /*<<< orphan*/  InterfaceData ;
typedef  int /*<<< orphan*/  HDEVINFO ;
typedef  int HANDLE ;
typedef  int /*<<< orphan*/  DeviceData ;
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CategoryGuid ; 
 int /*<<< orphan*/  CloseHandle (int) ; 
 int CreateFile (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DIGCF_DEVICEINTERFACE ; 
 int /*<<< orphan*/  DeviceIoControl (int,int /*<<< orphan*/ ,TYPE_11__*,int,TYPE_10__*,int,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FILE_ATTRIBUTE_NORMAL ; 
 int GENERIC_READ ; 
 int GENERIC_WRITE ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 scalar_t__ HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IOCTL_KS_PROPERTY ; 
 int /*<<< orphan*/  IOCTL_KS_WRITE_STREAM ; 
 int /*<<< orphan*/  KSDATAFORMAT_ATTRIBUTES ; 
 int /*<<< orphan*/  KSDATAFORMAT_SPECIFIER_WAVEFORMATEX ; 
 int /*<<< orphan*/  KSDATAFORMAT_SUBTYPE_PCM ; 
 int /*<<< orphan*/  KSDATAFORMAT_TYPE_AUDIO ; 
 int /*<<< orphan*/  KSINTERFACESETID_Standard ; 
 int /*<<< orphan*/  KSINTERFACE_STANDARD_STREAMING ; 
 int /*<<< orphan*/  KSMEDIUMSETID_Standard ; 
 int /*<<< orphan*/  KSMEDIUM_TYPE_ANYINSTANCE ; 
 int /*<<< orphan*/  KSPRIORITY_NORMAL ; 
 int /*<<< orphan*/  KSPROPERTY_CONNECTION_STATE ; 
 int /*<<< orphan*/  KSPROPERTY_TYPE_SET ; 
 int /*<<< orphan*/  KSPROPSETID_Connection ; 
 TYPE_10__ KSSTATE_RUN ; 
 TYPE_10__ KSSTATE_STOP ; 
 int /*<<< orphan*/  KsCreatePin (int,TYPE_12__*,int,int*) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 int /*<<< orphan*/  SetupDiDestroyDeviceInfoList (int /*<<< orphan*/ ) ; 
 int SetupDiEnumDeviceInterfaces (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,TYPE_8__*) ; 
 int /*<<< orphan*/  SetupDiGetClassDevs (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int SetupDiGetDeviceInterfaceDetail (int /*<<< orphan*/ ,TYPE_8__*,TYPE_9__*,int,int /*<<< orphan*/ *,TYPE_7__*) ; 
 int /*<<< orphan*/  WAVE_FORMAT_PCM ; 
 double _2pi ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 
 int sin (double) ; 
 int /*<<< orphan*/  wprintf (char*,int,char*) ; 

VOID
TestKs()
{
    SP_DEVICE_INTERFACE_DATA InterfaceData;
    SP_DEVINFO_DATA DeviceData;
    PSP_DEVICE_INTERFACE_DETAIL_DATA DetailData;
    HDEVINFO DeviceHandle;
    PKSDATAFORMAT_WAVEFORMATEX DataFormat;
    PKSPIN_CONNECT PinConnect;
    PKSSTREAM_HEADER Packet;
    PKSPROPERTY Property;
    KSSTATE State;
    DWORD Length;
    HANDLE FilterHandle; 
    HANDLE PinHandle;
    PSHORT SoundBuffer;
    UINT i = 0;
    BOOL Result;
    NTSTATUS Status;

  //
    // Get a handle to KS Audio Interfaces
    //
    DeviceHandle = SetupDiGetClassDevs(&CategoryGuid,
                                       NULL,
                                       NULL,
                                       DIGCF_DEVICEINTERFACE); //DIGCF_PRESENT

   printf("DeviceHandle %p\n", DeviceHandle);

    //
    // Enumerate the first interface
    //
    InterfaceData.cbSize = sizeof(InterfaceData);
    InterfaceData.Reserved = 0;
    Result = SetupDiEnumDeviceInterfaces(DeviceHandle,
                                NULL,
                                &CategoryGuid,
                                1,
                                &InterfaceData);

   printf("SetupDiEnumDeviceInterfaces %u Error %ld\n", Result, GetLastError());

    //
    // Get the interface details (namely the device path)
    //
    Length = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA) + MAX_PATH * sizeof(WCHAR);
    DetailData = (PSP_DEVICE_INTERFACE_DETAIL_DATA)HeapAlloc(GetProcessHeap(),
                                                             0,
                                                             Length);
    DetailData->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);
    DeviceData.cbSize = sizeof(DeviceData);
    DeviceData.Reserved = 0;
    Result = SetupDiGetDeviceInterfaceDetail(DeviceHandle,
                                    &InterfaceData,
                                    DetailData,
                                    Length,
                                    NULL,
                                    &DeviceData);

    wprintf(L"SetupDiGetDeviceInterfaceDetail %u Path DetailData %s\n", Result, (LPWSTR)&DetailData->DevicePath[0]);

    //
    // Open a handle to the device
    //
    FilterHandle = CreateFile(DetailData->DevicePath,
                              GENERIC_READ | GENERIC_WRITE,
                              0,
                              NULL,
                              OPEN_EXISTING,
                              FILE_ATTRIBUTE_NORMAL,
                              NULL);

    printf("Handle %p\n", FilterHandle);

    //
    // Close the interface handle and clean up
    //
    SetupDiDestroyDeviceInfoList(DeviceHandle);

    //
    // Allocate a KS Pin Connection Request Structure
    //
    Length = sizeof(KSPIN_CONNECT) + sizeof(KSDATAFORMAT_WAVEFORMATEX);
	printf("Length %ld KSPIN %Iu DATAFORMAT %Iu\n", Length, sizeof(KSPIN_CONNECT), sizeof(KSDATAFORMAT_WAVEFORMATEX));
    PinConnect = (PKSPIN_CONNECT)HeapAlloc(GetProcessHeap(), 0, Length);
    DataFormat = (PKSDATAFORMAT_WAVEFORMATEX)(PinConnect + 1);

    //
    // Setup the KS Pin Data
    //
    PinConnect->Interface.Set = KSINTERFACESETID_Standard;
    PinConnect->Interface.Id = KSINTERFACE_STANDARD_STREAMING;
    PinConnect->Interface.Flags = 0;
    PinConnect->Medium.Set = KSMEDIUMSETID_Standard;
    PinConnect->Medium.Id = KSMEDIUM_TYPE_ANYINSTANCE;
    PinConnect->Medium.Flags = 0;
    PinConnect->PinId = 0;
    PinConnect->PinToHandle = NULL;
    PinConnect->Priority.PriorityClass = KSPRIORITY_NORMAL;
    PinConnect->Priority.PrioritySubClass = 1;

    //
    // Setup the KS Data Format Information
    //
    DataFormat->WaveFormatEx.wFormatTag = WAVE_FORMAT_PCM;
    DataFormat->WaveFormatEx.nChannels = 2;
    DataFormat->WaveFormatEx.nSamplesPerSec = 48000;
    DataFormat->WaveFormatEx.nBlockAlign = 4;
    DataFormat->WaveFormatEx.nAvgBytesPerSec = 48000 * 4;
    DataFormat->WaveFormatEx.wBitsPerSample = 16;
    DataFormat->WaveFormatEx.cbSize = 0;
    DataFormat->DataFormat.FormatSize = sizeof(KSDATAFORMAT) +
                                        sizeof(WAVEFORMATEX);
    DataFormat->DataFormat.Flags = KSDATAFORMAT_ATTRIBUTES;
    DataFormat->DataFormat.Reserved = 0;
    DataFormat->DataFormat.MajorFormat = KSDATAFORMAT_TYPE_AUDIO;
    DataFormat->DataFormat.SubFormat = KSDATAFORMAT_SUBTYPE_PCM;
    DataFormat->DataFormat.Specifier = KSDATAFORMAT_SPECIFIER_WAVEFORMATEX;
    DataFormat->DataFormat.SampleSize = 4;

    //
    // Create the pin
    //
    Status = KsCreatePin(FilterHandle, PinConnect, GENERIC_WRITE, &PinHandle);

    printf("PinHandle %p Status %lx\n", PinHandle, Status);

    //
    // Allocate a buffer for 1 second
    //
    Length = 48000 * 4;
    SoundBuffer = (PSHORT)HeapAlloc(GetProcessHeap(), 0, Length);

    //
    // Fill the buffer with a 500 Hz sine tone
    //
    while (i < Length / 2)
    {
        //
        // Generate the wave for each channel:
        // Amplitude * sin( Sample * Frequency * 2PI / SamplesPerSecond )
        //
        SoundBuffer[i] = 0x7FFF * sin(0.5 * (i - 1) * 500 * _2pi / 48000);
        i++;
        SoundBuffer[i] = 0x7FFF * sin((0.5 * i - 2) * 500 * _2pi / 48000);
        i++;
    }

    //
    // Create and fill out the KS Stream Packet
    //
    Packet = (PKSSTREAM_HEADER)HeapAlloc(GetProcessHeap(),
                                         HEAP_ZERO_MEMORY,
                                         sizeof(KSSTREAM_HEADER));
    Packet->Data = SoundBuffer;
    Packet->FrameExtent = Length;
    Packet->DataUsed = Length;
    Packet->Size = sizeof(KSSTREAM_HEADER);
    Packet->PresentationTime.Numerator = 1;
    Packet->PresentationTime.Denominator = 1;

    //
    // Setup a KS Property to change the state
    //
    Property = (PKSPROPERTY)HeapAlloc(GetProcessHeap(), 0, sizeof(KSPROPERTY));
    Property->Set = KSPROPSETID_Connection;
    Property->Id = KSPROPERTY_CONNECTION_STATE;
    Property->Flags = KSPROPERTY_TYPE_SET;

    //
    // Change the state to run
    //
    State = KSSTATE_RUN;
    DeviceIoControl(PinHandle,
                    IOCTL_KS_PROPERTY,
                    Property,
                    sizeof(KSPROPERTY),
                    &State,
                    sizeof(State),
                    &Length,
                    NULL);

    //
    // Play our 1-second buffer
    //
    DeviceIoControl(PinHandle,
                    IOCTL_KS_WRITE_STREAM,
                    NULL,
                    0,
                    Packet,
                    Packet->Size,
                    &Length,
                    NULL);

    //
    // Change the state to stop
    //
    State = KSSTATE_STOP;
    DeviceIoControl(PinHandle,
                    IOCTL_KS_PROPERTY,
                    Property,
                    sizeof(KSPROPERTY),
                    &State,
                    sizeof(State),
                    &Length,
                    NULL);

    CloseHandle(PinHandle);
    CloseHandle(FilterHandle);
}