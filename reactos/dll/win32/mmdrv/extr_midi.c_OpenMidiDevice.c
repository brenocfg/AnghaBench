#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT ;
struct TYPE_9__ {int /*<<< orphan*/  hMidi; int /*<<< orphan*/  dwInstance; int /*<<< orphan*/  dwCallback; } ;
struct TYPE_8__ {TYPE_1__* Bufs; } ;
struct TYPE_7__ {int DeviceType; int /*<<< orphan*/ * AuxEvent2; int /*<<< orphan*/ * AuxEvent1; void* Event; int /*<<< orphan*/  DeviceHandle; scalar_t__ dwFlags; int /*<<< orphan*/  hMidi; int /*<<< orphan*/  dwInstance; int /*<<< orphan*/  dwCallback; TYPE_3__* Mid; } ;
struct TYPE_6__ {TYPE_2__* pClient; } ;
typedef  TYPE_2__* PMIDIALLOC ;
typedef  TYPE_3__* PLOCALMIDIDATA ;
typedef  scalar_t__ MMRESULT ;
typedef  int /*<<< orphan*/  MIDIALLOC ;
typedef  TYPE_4__* LPMIDIOPENDESC ;
typedef  int /*<<< orphan*/  LOCALMIDIDATA ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 void* CreateEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DPRINT (char*) ; 
 int /*<<< orphan*/  FALSE ; 
 int GENERIC_READ ; 
 int GENERIC_WRITE ; 
 int /*<<< orphan*/  Heap ; 
 int /*<<< orphan*/  HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  INFINITE ; 
 int LOCAL_MIDI_BUFFERS ; 
 scalar_t__ MMSYSERR_NOERROR ; 
 scalar_t__ MMSYSERR_NOMEM ; 
#define  MidiInDevice 129 
#define  MidiOutDevice 128 
 scalar_t__ OpenDevice (int,scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  WaitForSingleObject (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static DWORD OpenMidiDevice(UINT DeviceType, DWORD ID, DWORD User, DWORD Param1, DWORD Param2)
{
    PMIDIALLOC pClient = NULL;
    MMRESULT Result = MMSYSERR_NOERROR;
    
    // Check ID?
    DPRINT("OpenMidiDevice()\n");
    
    switch(DeviceType)
    {
        case MidiOutDevice :
            pClient = (PMIDIALLOC) HeapAlloc(Heap, 0, sizeof(MIDIALLOC));
            if ( pClient ) memset(pClient, 0, sizeof(MIDIALLOC));
            break;
        
        case MidiInDevice :
            pClient = (PMIDIALLOC) HeapAlloc(Heap, 0, sizeof(MIDIALLOC) + sizeof(LOCALMIDIDATA));
			if ( pClient ) memset(pClient, 0, sizeof(MIDIALLOC) + sizeof(LOCALMIDIDATA));
            break;
    };
    
    if ( !pClient )
        return MMSYSERR_NOMEM;
    
	if (DeviceType == MidiInDevice) 
	{
        int i;
        pClient->Mid = (PLOCALMIDIDATA)(pClient + 1);
        for (i = 0 ;i < LOCAL_MIDI_BUFFERS ; i++) 
		{
            pClient->Mid->Bufs[i].pClient = pClient;
        }
    }

    pClient->DeviceType = DeviceType;
    pClient->dwCallback = ((LPMIDIOPENDESC)Param1)->dwCallback;
    pClient->dwInstance = ((LPMIDIOPENDESC)Param1)->dwInstance;
    pClient->hMidi = ((LPMIDIOPENDESC)Param1)->hMidi;
    pClient->dwFlags = Param2;
    
    Result = OpenDevice(DeviceType, ID, &pClient->DeviceHandle, (GENERIC_READ | GENERIC_WRITE));
    
    if ( Result != MMSYSERR_NOERROR )
    {
        // cleanup
        return Result;
    }
    
    pClient->Event = CreateEvent(NULL, FALSE, FALSE, NULL);
    
    if ( !pClient->Event )
    {
        // cleanup
        return MMSYSERR_NOMEM;
    }

	if (DeviceType == MidiInDevice) 
	{

        pClient->AuxEvent1 = CreateEvent(NULL, FALSE, FALSE, NULL);
        if (pClient->AuxEvent1 == NULL) 
		{
            // cleanup
            return MMSYSERR_NOMEM;
        }
        
		pClient->AuxEvent2 = CreateEvent(NULL, FALSE, FALSE, NULL);
        if (pClient->AuxEvent2 == NULL) 
		{
            // cleanup
            return MMSYSERR_NOMEM;
        }

        
        // TaskCreate
        
        
       WaitForSingleObject(pClient->AuxEvent2, INFINITE);
    }

    PMIDIALLOC *pUserHandle;
    pUserHandle = (PMIDIALLOC*) User;
    *pUserHandle = pClient;
    
    // callback    

    return MMSYSERR_NOERROR;
}