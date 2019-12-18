#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_5__ {TYPE_2__ IAVIStream_iface; } ;
typedef  int /*<<< orphan*/ * REFIID ;
typedef  int /*<<< orphan*/ * LPVOID ;
typedef  TYPE_1__ IAVIStreamImpl ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  AVIERR_MEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  IAVIStream_QueryInterface (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  iacmst ; 

HRESULT AVIFILE_CreateACMStream(REFIID riid, LPVOID *ppv)
{
  IAVIStreamImpl *pstream;
  HRESULT         hr;

  assert(riid != NULL && ppv != NULL);

  *ppv = NULL;

  pstream = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(IAVIStreamImpl));
  if (pstream == NULL)
    return AVIERR_MEMORY;

  pstream->IAVIStream_iface.lpVtbl = &iacmst;

  hr = IAVIStream_QueryInterface(&pstream->IAVIStream_iface, riid, ppv);
  if (FAILED(hr))
    HeapFree(GetProcessHeap(), 0, pstream);

  return hr;
}