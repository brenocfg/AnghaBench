#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct MMIOPos {int dwSize; int /*<<< orphan*/  dwOffset; } ;
struct AviListBuild {int numVideoFrames; int inVideoSize; int numAudioBlocks; int numAudioAllocated; int inAudioSize; } ;
struct TYPE_9__ {int /*<<< orphan*/  fccHandler; } ;
struct TYPE_11__ {int video_stream_n; int dwPlayableVideoFrames; int audio_stream_n; struct MMIOPos* lpAudioIndex; int /*<<< orphan*/  lpWaveFormat; TYPE_3__* lpVideoIndex; TYPE_2__ ash_video; TYPE_1__* inbih; } ;
typedef  TYPE_4__ WINE_MCIAVI ;
struct TYPE_12__ {scalar_t__ ckid; int cksize; int /*<<< orphan*/  dwDataOffset; } ;
struct TYPE_10__ {int dwSize; int /*<<< orphan*/  dwOffset; } ;
struct TYPE_8__ {scalar_t__ biCompression; } ;
typedef  int LPSTR ;
typedef  TYPE_5__* LPMMCKINFO ;
typedef  int DWORD ;
typedef  char BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 struct MMIOPos* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct MMIOPos* HeapReAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct MMIOPos*,int) ; 
 int LOWORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int,...) ; 
 int /*<<< orphan*/  TRUE ; 
 int TWOCCFromFOURCC (scalar_t__) ; 
 int /*<<< orphan*/  WARN (char*,...) ; 
 scalar_t__ ckidAVIPADDING ; 
#define  cktypeDIBbits 131 
#define  cktypeDIBcompressed 130 
#define  cktypePALchange 129 
#define  cktypeWAVEbytes 128 
 int /*<<< orphan*/  isxdigit (char const) ; 
 char tolower (char const) ; 

__attribute__((used)) static BOOL	MCIAVI_AddFrame(WINE_MCIAVI* wma, LPMMCKINFO mmck,
				struct AviListBuild* alb)
{
    const BYTE *p;
    DWORD stream_n;
    DWORD twocc;

    if (mmck->ckid == ckidAVIPADDING) return TRUE;

    p = (const BYTE *)&mmck->ckid;

    if (!isxdigit(p[0]) || !isxdigit(p[1]))
    {
        WARN("wrongly encoded stream #\n");
        return FALSE;
    }

    stream_n = (p[0] <= '9') ? (p[0] - '0') : (tolower(p[0]) - 'a' + 10);
    stream_n <<= 4;
    stream_n |= (p[1] <= '9') ? (p[1] - '0') : (tolower(p[1]) - 'a' + 10);

    TRACE("ckid %4.4s (stream #%d)\n", (LPSTR)&mmck->ckid, stream_n);

    /* Some (rare?) AVI files have video streams name XXYY where XX = stream number and YY = TWOCC
     * of the last 2 characters of the biCompression member of the BITMAPINFOHEADER structure.
     * Ex: fccHandler = IV32 & biCompression = IV32 => stream name = XX32
     *     fccHandler = MSVC & biCompression = CRAM => stream name = XXAM
     * Another possibility is that these TWOCC are simply ignored.
     * Default to cktypeDIBcompressed when this case happens.
     */
    twocc = TWOCCFromFOURCC(mmck->ckid);
    if (twocc == TWOCCFromFOURCC(wma->inbih->biCompression))
        twocc = cktypeDIBcompressed;
    /* Also detect some chunks that seem to be used by Indeo videos where the chunk is named
     * after the codec. */
    else if (twocc == LOWORD(wma->ash_video.fccHandler))
        twocc = cktypeDIBcompressed;
    switch (twocc) {
    case cktypeDIBbits:
    case cktypeDIBcompressed:
    case cktypePALchange:
        if (stream_n != wma->video_stream_n)
        {
            TRACE("data belongs to another video stream #%d\n", stream_n);
            return FALSE;
        }

	TRACE("Adding video frame[%d]: %d bytes\n",
	      alb->numVideoFrames, mmck->cksize);

	if (alb->numVideoFrames < wma->dwPlayableVideoFrames) {
	    wma->lpVideoIndex[alb->numVideoFrames].dwOffset = mmck->dwDataOffset;
	    wma->lpVideoIndex[alb->numVideoFrames].dwSize = mmck->cksize;
	    if (alb->inVideoSize < mmck->cksize)
		alb->inVideoSize = mmck->cksize;
	    alb->numVideoFrames++;
	} else {
	    WARN("Too many video frames\n");
	}
	break;
    case cktypeWAVEbytes:
        if (stream_n != wma->audio_stream_n)
        {
            TRACE("data belongs to another audio stream #%d\n", stream_n);
            return FALSE;
        }

	TRACE("Adding audio frame[%d]: %d bytes\n",
	      alb->numAudioBlocks, mmck->cksize);
	if (wma->lpWaveFormat) {
	    if (alb->numAudioBlocks >= alb->numAudioAllocated) {
                DWORD newsize = alb->numAudioAllocated + 32;
                struct MMIOPos* newindex;

                if (!wma->lpAudioIndex)
                    newindex = HeapAlloc(GetProcessHeap(), 0, newsize * sizeof(struct MMIOPos));
                else
                    newindex = HeapReAlloc(GetProcessHeap(), 0, wma->lpAudioIndex, newsize * sizeof(struct MMIOPos));
                if (!newindex) return FALSE;
                alb->numAudioAllocated = newsize;
                wma->lpAudioIndex = newindex;
	    }
	    wma->lpAudioIndex[alb->numAudioBlocks].dwOffset = mmck->dwDataOffset;
	    wma->lpAudioIndex[alb->numAudioBlocks].dwSize = mmck->cksize;
	    if (alb->inAudioSize < mmck->cksize)
		alb->inAudioSize = mmck->cksize;
	    alb->numAudioBlocks++;
	} else {
	    WARN("Wave chunk without wave format... discarding\n");
	}
	break;
    default:
        WARN("Unknown frame type %4.4s\n", (LPSTR)&mmck->ckid);
	break;
    }
    return TRUE;
}