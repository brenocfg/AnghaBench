#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * ppPins; } ;
struct TYPE_5__ {TYPE_1__ Parser; } ;
typedef  int /*<<< orphan*/  IPin ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int DWORD ;
typedef  TYPE_2__ AVISplitterImpl ;

/* Variables and functions */
 int /*<<< orphan*/  IPin_ConnectedTo (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IPin_EndOfStream (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPin_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_FALSE ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 

__attribute__((used)) static HRESULT AVISplitter_SendEndOfFile(AVISplitterImpl *This, DWORD streamnumber)
{
    IPin* ppin = NULL;
    HRESULT hr;

    TRACE("End of file reached\n");

    hr = IPin_ConnectedTo(This->Parser.ppPins[streamnumber+1], &ppin);
    if (SUCCEEDED(hr))
    {
        hr = IPin_EndOfStream(ppin);
        IPin_Release(ppin);
    }
    TRACE("--> %x\n", hr);

    /* Force the pullpin thread to stop */
    return S_FALSE;
}