#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int ULONGLONG ;
typedef  int LONGLONG ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int) ; 
 int /*<<< orphan*/  E_INVALIDARG ; 
 int /*<<< orphan*/  FIXME (char*,int,int,int,int) ; 
 scalar_t__ MPEGSplitter_head_check (int*) ; 
 scalar_t__ MPEG_AUDIO_HEADER ; 
 int /*<<< orphan*/  S_OK ; 
 int* freqs ; 
 int*** tabsel_123 ; 

__attribute__((used)) static HRESULT parse_header(BYTE *header, LONGLONG *plen, LONGLONG *pduration)
{
    int bitrate_index, freq_index, lsf = 1, mpeg1, layer, padding, bitrate, length;
    LONGLONG duration;

    if (MPEGSplitter_head_check(header) != MPEG_AUDIO_HEADER)
    {
        FIXME("Not a valid header: %02x:%02x:%02x:%02x\n", header[0], header[1], header[2], header[3]);
        return E_INVALIDARG;
    }

    mpeg1 = (header[1]>>4)&0x1;
    if (mpeg1)
        lsf = ((header[1]>>3)&0x1)^1;

    layer = 4-((header[1]>>1)&0x3);
    bitrate_index = ((header[2]>>4)&0xf);
    freq_index = ((header[2]>>2)&0x3) + (mpeg1?(lsf*3):6);
    padding = ((header[2]>>1)&0x1);

    bitrate = tabsel_123[lsf][layer-1][bitrate_index] * 1000;
    if (!bitrate)
    {
        FIXME("Not a valid header: %02x:%02x:%02x:%02x\n", header[0], header[1], header[2], header[3]);
        return E_INVALIDARG;
    }

    if (layer == 1)
        length = 4 * (12 * bitrate / freqs[freq_index] + padding);
    else if (layer == 2)
        length = 144 * bitrate / freqs[freq_index] + padding;
    else if (layer == 3)
        length = 144 * bitrate / (freqs[freq_index]<<lsf) + padding;
    else
    {
        ERR("Impossible layer %d\n", layer);
        return E_INVALIDARG;
    }

    duration = (ULONGLONG)10000000 * (ULONGLONG)(length) / (ULONGLONG)(bitrate/8);
    *plen = length;
    if (pduration)
        *pduration += duration;
    return S_OK;
}