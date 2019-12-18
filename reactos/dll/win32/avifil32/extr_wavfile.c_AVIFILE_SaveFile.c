#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wfx ;
typedef  int /*<<< orphan*/  dwFactLength ;
struct TYPE_15__ {int /*<<< orphan*/  nBlockAlign; scalar_t__ wFormatTag; } ;
typedef  TYPE_3__ WAVEFORMATEX ;
struct TYPE_18__ {scalar_t__ wFormatTag; } ;
struct TYPE_14__ {scalar_t__ cb; int /*<<< orphan*/ * lp; } ;
struct TYPE_13__ {scalar_t__ cksize; int dwDataOffset; } ;
struct TYPE_17__ {int cbFormat; int /*<<< orphan*/  hmmio; TYPE_2__ extra; TYPE_1__ ckData; TYPE_8__* lpFormat; } ;
struct TYPE_16__ {int cksize; int /*<<< orphan*/  ckid; int /*<<< orphan*/  fccType; } ;
typedef  int /*<<< orphan*/  PCMWAVEFORMAT ;
typedef  TYPE_4__ MMCKINFO ;
typedef  TYPE_5__ IAVIFileImpl ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/ * HPSTR ;
typedef  int /*<<< orphan*/  HACMSTREAM ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ACM_FORMATSUGGESTF_WFORMATTAG ; 
 int /*<<< orphan*/  ACM_STREAMOPENF_NONREALTIME ; 
 int /*<<< orphan*/  ACM_STREAMSIZEF_SOURCE ; 
 int /*<<< orphan*/  AVIERR_FILEWRITE ; 
 int /*<<< orphan*/  AVIERR_OK ; 
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  MMIO_CREATERIFF ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ S_OK ; 
 scalar_t__ WAVE_FORMAT_PCM ; 
 scalar_t__ acmFormatSuggest (int /*<<< orphan*/ *,TYPE_8__*,TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acmStreamClose (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acmStreamOpen (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_8__*,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acmStreamSize (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ckidAVIPADDING ; 
 int /*<<< orphan*/  ckidWAVEDATA ; 
 int /*<<< orphan*/  ckidWAVEFACT ; 
 int /*<<< orphan*/  ckidWAVEFORMAT ; 
 int /*<<< orphan*/  formtypeWAVE ; 
 scalar_t__ mmioAscend (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ mmioCreateChunk (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ mmioFlush (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mmioSeek (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ mmioWrite (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static HRESULT AVIFILE_SaveFile(const IAVIFileImpl *This)
{
  MMCKINFO ckRIFF;
  MMCKINFO ck;

  mmioSeek(This->hmmio, 0, SEEK_SET);

  /* create the RIFF chunk with formtype WAVE */
  ckRIFF.fccType = formtypeWAVE;
  ckRIFF.cksize  = 0;
  if (mmioCreateChunk(This->hmmio, &ckRIFF, MMIO_CREATERIFF) != S_OK)
    return AVIERR_FILEWRITE;

  /* the next chunk is the format */
  ck.ckid   = ckidWAVEFORMAT;
  ck.cksize = This->cbFormat;
  if (mmioCreateChunk(This->hmmio, &ck, 0) != S_OK)
    return AVIERR_FILEWRITE;
  if (This->lpFormat != NULL && This->cbFormat > 0) {
    if (mmioWrite(This->hmmio, (HPSTR)This->lpFormat, ck.cksize) != ck.cksize)
      return AVIERR_FILEWRITE;
  }
  if (mmioAscend(This->hmmio, &ck, 0) != S_OK)
    return AVIERR_FILEWRITE;

  /* fact chunk is needed for non-pcm waveforms */
  if (This->lpFormat != NULL && This->cbFormat > sizeof(PCMWAVEFORMAT) &&
      This->lpFormat->wFormatTag != WAVE_FORMAT_PCM) {
    WAVEFORMATEX wfx;
    DWORD        dwFactLength;
    HACMSTREAM   has;

    /* try to open an appropriate audio codec to figure out
     * data for fact-chunk */
    wfx.wFormatTag = WAVE_FORMAT_PCM;
    if (acmFormatSuggest(NULL, This->lpFormat, &wfx,
			 sizeof(wfx), ACM_FORMATSUGGESTF_WFORMATTAG)) {
      acmStreamOpen(&has, NULL, This->lpFormat, &wfx, NULL,
		    0, 0, ACM_STREAMOPENF_NONREALTIME);
      acmStreamSize(has, This->ckData.cksize, &dwFactLength,
		    ACM_STREAMSIZEF_SOURCE);
      dwFactLength /= wfx.nBlockAlign;
      acmStreamClose(has, 0);

      /* create the fact chunk */
      ck.ckid   = ckidWAVEFACT;
      ck.cksize = sizeof(dwFactLength);

      /* test for enough space before data chunk */
      if (mmioSeek(This->hmmio, 0, SEEK_CUR) > This->ckData.dwDataOffset
	  - ck.cksize - 4 * sizeof(DWORD))
	return AVIERR_FILEWRITE;
      if (mmioCreateChunk(This->hmmio, &ck, 0) != S_OK)
	return AVIERR_FILEWRITE;
      if (mmioWrite(This->hmmio, (HPSTR)&dwFactLength, ck.cksize) != ck.cksize)
	return AVIERR_FILEWRITE;
      if (mmioAscend(This->hmmio, &ck, 0) != S_OK)
	return AVIERR_FILEWRITE;
    } else
      ERR(": fact chunk is needed for non-pcm files -- currently no codec found, so skipped!\n");
  }

  /* if there was extra stuff, we need to fill it with JUNK */
  if (mmioSeek(This->hmmio, 0, SEEK_CUR) + 2 * sizeof(DWORD) < This->ckData.dwDataOffset) {
    ck.ckid   = ckidAVIPADDING;
    ck.cksize = 0;
    if (mmioCreateChunk(This->hmmio, &ck, 0) != S_OK)
      return AVIERR_FILEWRITE;

    if (mmioSeek(This->hmmio, This->ckData.dwDataOffset
		 - 2 * sizeof(DWORD), SEEK_SET) == -1)
      return AVIERR_FILEWRITE;
    if (mmioAscend(This->hmmio, &ck, 0) != S_OK)
      return AVIERR_FILEWRITE;
  }

  /* create the data chunk */
  ck.ckid   = ckidWAVEDATA;
  ck.cksize = This->ckData.cksize;
  if (mmioCreateChunk(This->hmmio, &ck, 0) != S_OK)
    return AVIERR_FILEWRITE;
  if (mmioSeek(This->hmmio, This->ckData.cksize, SEEK_CUR) == -1)
    return AVIERR_FILEWRITE;
  if (mmioAscend(This->hmmio, &ck, 0) != S_OK)
    return AVIERR_FILEWRITE;

  /* some optional extra chunks? */
  if (This->extra.lp != NULL && This->extra.cb > 0) {
    /* chunk headers are already in structure */
    if (mmioWrite(This->hmmio, This->extra.lp, This->extra.cb) != This->extra.cb)
      return AVIERR_FILEWRITE;
  }

  /* close RIFF chunk */
  if (mmioAscend(This->hmmio, &ckRIFF, 0) != S_OK)
    return AVIERR_FILEWRITE;
  if (mmioFlush(This->hmmio, 0) != S_OK)
    return AVIERR_FILEWRITE;

  return AVIERR_OK;
}