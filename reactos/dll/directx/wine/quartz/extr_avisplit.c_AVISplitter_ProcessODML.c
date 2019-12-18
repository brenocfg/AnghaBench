#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int cb; int /*<<< orphan*/ * dwFuture; int /*<<< orphan*/  dwGrandFrames; } ;
struct TYPE_6__ {TYPE_3__ ExtHeader; } ;
struct TYPE_5__ {scalar_t__ cb; int fcc; } ;
typedef  TYPE_1__ RIFFCHUNK ;
typedef  int LPCSTR ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  TYPE_2__ AVISplitterImpl ;
typedef  TYPE_3__ AVIEXTHEADER ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,int,...) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
#define  ckidAVIEXTHEADER 128 

__attribute__((used)) static HRESULT AVISplitter_ProcessODML(AVISplitterImpl * This, const BYTE * pData, DWORD cb)
{
    const RIFFCHUNK * pChunk;

    for (pChunk = (const RIFFCHUNK *)pData;
         ((const BYTE *)pChunk >= pData) && ((const BYTE *)pChunk + sizeof(RIFFCHUNK) < pData + cb) && (pChunk->cb > 0);
         pChunk = (const RIFFCHUNK *)((const BYTE*)pChunk + sizeof(RIFFCHUNK) + pChunk->cb)
        )
    {
        switch (pChunk->fcc)
        {
        case ckidAVIEXTHEADER:
            {
                int x;
                const AVIEXTHEADER * pExtHdr = (const AVIEXTHEADER *)pChunk;

                TRACE("processing extension header\n");
                if (pExtHdr->cb != sizeof(AVIEXTHEADER) - sizeof(RIFFCHUNK))
                {
                    FIXME("Size: %u\n", pExtHdr->cb);
                    break;
                }
                TRACE("dwGrandFrames: %u\n", pExtHdr->dwGrandFrames);
                for (x = 0; x < 61; ++x)
                    if (pExtHdr->dwFuture[x])
                        FIXME("dwFuture[%i] = %u (0x%08x)\n", x, pExtHdr->dwFuture[x], pExtHdr->dwFuture[x]);
                This->ExtHeader = *pExtHdr;
                break;
            }
        default:
            FIXME("unknown chunk type \"%.04s\" ignored\n", (LPCSTR)&pChunk->fcc);
        }
    }

    return S_OK;
}