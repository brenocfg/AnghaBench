#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int WORD ;
struct TYPE_8__ {int /*<<< orphan*/  dwFlags; int /*<<< orphan*/  dwChunkOffset; int /*<<< orphan*/  dwChunkLength; int /*<<< orphan*/  ckid; } ;
struct TYPE_6__ {int dwStreams; } ;
struct TYPE_7__ {int /*<<< orphan*/ * ppStreams; int /*<<< orphan*/  dwMoviChunkPos; TYPE_1__ fInfo; } ;
typedef  scalar_t__ LONG ;
typedef  TYPE_2__ IAVIFileImpl ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ DWORD ;
typedef  scalar_t__ BOOL ;
typedef  TYPE_3__ AVIINDEXENTRY ;

/* Variables and functions */
 int /*<<< orphan*/  AVIERR_BADFORMAT ; 
 int /*<<< orphan*/  AVIERR_BADPARAM ; 
 int /*<<< orphan*/  AVIERR_MEMORY ; 
 int /*<<< orphan*/  AVIERR_OK ; 
 int /*<<< orphan*/  AVIFILE_AddFrame (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 scalar_t__ FALSE ; 
 int StreamFromFOURCC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  listtypeAVIRECORD ; 

__attribute__((used)) static HRESULT AVIFILE_ParseIndex(const IAVIFileImpl *This, AVIINDEXENTRY *lp,
				  LONG count, DWORD pos, BOOL *bAbsolute)
{
  if (lp == NULL)
    return AVIERR_BADPARAM;

  for (; count > 0; count--, lp++) {
    WORD nStream = StreamFromFOURCC(lp->ckid);

    if (lp->ckid == listtypeAVIRECORD || nStream == 0x7F)
      continue; /* skip these */

    if (nStream > This->fInfo.dwStreams)
      return AVIERR_BADFORMAT;

    /* Video frames can be either indexed in a relative position to the
     * "movi" chunk or in a absolute position in the file. If the index
     * is relative the frame offset will always be so small that it will
     * virtually never reach the "movi" offset so we can detect if the
     * video is relative very fast.
     */
    if (*bAbsolute && lp->dwChunkOffset < This->dwMoviChunkPos)
      *bAbsolute = FALSE;

    if (!*bAbsolute)
      lp->dwChunkOffset += pos; /* make the offset absolute */

    if (FAILED(AVIFILE_AddFrame(This->ppStreams[nStream], lp->ckid, lp->dwChunkLength, lp->dwChunkOffset, lp->dwFlags)))
      return AVIERR_MEMORY;
  }

  return AVIERR_OK;
}