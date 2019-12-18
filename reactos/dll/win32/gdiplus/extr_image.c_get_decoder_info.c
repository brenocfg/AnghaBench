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
struct TYPE_4__ {int Flags; scalar_t__ SigSize; size_t SigCount; int* SigPattern; int* SigMask; } ;
struct image_codec {TYPE_1__ info; } ;
typedef  scalar_t__ UINT ;
struct TYPE_5__ {scalar_t__ QuadPart; } ;
typedef  TYPE_2__ LARGE_INTEGER ;
typedef  int /*<<< orphan*/  IStream ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  GpStatus ;
typedef  size_t DWORD ;
typedef  int const BYTE ;

/* Variables and functions */
 scalar_t__ FAILED (scalar_t__) ; 
 int /*<<< orphan*/  GenericError ; 
 scalar_t__ IStream_Read (int /*<<< orphan*/ *,int const*,int,scalar_t__*) ; 
 scalar_t__ IStream_Seek (int /*<<< orphan*/ *,TYPE_2__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ImageCodecFlagsDecoder ; 
 int NUM_CODECS ; 
 int /*<<< orphan*/  Ok ; 
 int /*<<< orphan*/  STREAM_SEEK_SET ; 
 scalar_t__ S_FALSE ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__,int const,int const,int const,int const,int const,int const,int const,int const) ; 
 struct image_codec* codecs ; 
 int /*<<< orphan*/  hresult_to_status (scalar_t__) ; 

__attribute__((used)) static GpStatus get_decoder_info(IStream* stream, const struct image_codec **result)
{
    BYTE signature[8];
    const BYTE *pattern, *mask;
    LARGE_INTEGER seek;
    HRESULT hr;
    UINT bytesread;
    int i;
    DWORD j, sig;

    /* seek to the start of the stream */
    seek.QuadPart = 0;
    hr = IStream_Seek(stream, seek, STREAM_SEEK_SET, NULL);
    if (FAILED(hr)) return hresult_to_status(hr);

    /* read the first 8 bytes */
    /* FIXME: This assumes all codecs have signatures <= 8 bytes in length */
    hr = IStream_Read(stream, signature, 8, &bytesread);
    if (FAILED(hr)) return hresult_to_status(hr);
    if (hr == S_FALSE || bytesread == 0) return GenericError;

    for (i = 0; i < NUM_CODECS; i++) {
        if ((codecs[i].info.Flags & ImageCodecFlagsDecoder) &&
            bytesread >= codecs[i].info.SigSize)
        {
            for (sig=0; sig<codecs[i].info.SigCount; sig++)
            {
                pattern = &codecs[i].info.SigPattern[codecs[i].info.SigSize*sig];
                mask = &codecs[i].info.SigMask[codecs[i].info.SigSize*sig];
                for (j=0; j<codecs[i].info.SigSize; j++)
                    if ((signature[j] & mask[j]) != pattern[j])
                        break;
                if (j == codecs[i].info.SigSize)
                {
                    *result = &codecs[i];
                    return Ok;
                }
            }
        }
    }

    TRACE("no match for %i byte signature %x %x %x %x %x %x %x %x\n", bytesread,
        signature[0],signature[1],signature[2],signature[3],
        signature[4],signature[5],signature[6],signature[7]);

    return GenericError;
}