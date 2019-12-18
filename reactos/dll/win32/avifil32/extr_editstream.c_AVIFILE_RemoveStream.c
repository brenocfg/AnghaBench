#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ dwStart; scalar_t__ dwLength; int /*<<< orphan*/ * pStream; } ;
struct TYPE_6__ {size_t nStreams; TYPE_2__* pStreams; } ;
typedef  TYPE_1__ IAVIEditStreamImpl ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  size_t DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  AVIERR_OK ; 
 scalar_t__ EditStreamEnd (TYPE_1__* const,size_t) ; 
 int /*<<< orphan*/  IAVIStream_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memmove (TYPE_2__*,TYPE_2__*,size_t) ; 

__attribute__((used)) static HRESULT AVIFILE_RemoveStream(IAVIEditStreamImpl* const This, DWORD nr)
{
  assert(This != NULL);
  assert(nr < This->nStreams);

  /* remove part nr */
  IAVIStream_Release(This->pStreams[nr].pStream);
  This->nStreams--;
  if (nr < This->nStreams)
    memmove(&This->pStreams[nr], &This->pStreams[nr + 1],
            (This->nStreams - nr) * sizeof(This->pStreams[0]));
  This->pStreams[This->nStreams].pStream  = NULL;
  This->pStreams[This->nStreams].dwStart  = 0;
  This->pStreams[This->nStreams].dwLength = 0;

  /* try to merge the part before the deleted one and the one after it */
  if (0 < nr && 0 < This->nStreams &&
      This->pStreams[nr - 1].pStream == This->pStreams[nr].pStream) {
    if (EditStreamEnd(This, nr - 1) == This->pStreams[nr].dwStart) {
      This->pStreams[nr - 1].dwLength += This->pStreams[nr].dwLength;
      return AVIFILE_RemoveStream(This, nr);
    }
  }

  return AVIERR_OK;
}