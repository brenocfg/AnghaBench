#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct wasapi_sample_fmt {int bits; int used_msb; int /*<<< orphan*/  mp_format; } ;
struct mp_chmap {int dummy; } ;
struct TYPE_5__ {scalar_t__ nSamplesPerSec; } ;
typedef  TYPE_1__ WAVEFORMATEX ;

/* Variables and functions */
 char* af_fmt_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chmap_from_waveformat (struct mp_chmap*,TYPE_1__*) ; 
 struct wasapi_sample_fmt format_from_waveformat (TYPE_1__*) ; 
 char* mp_chmap_to_str (struct mp_chmap*) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char*,char*,int,int,unsigned int) ; 

__attribute__((used)) static char *waveformat_to_str_buf(char *buf, size_t buf_size, WAVEFORMATEX *wf)
{
    struct mp_chmap channels;
    chmap_from_waveformat(&channels, wf);

    struct wasapi_sample_fmt format = format_from_waveformat(wf);

    snprintf(buf, buf_size, "%s %s (%d/%d bits) @ %uhz",
             mp_chmap_to_str(&channels),
             af_fmt_to_str(format.mp_format), format.bits, format.used_msb,
             (unsigned) wf->nSamplesPerSec);
    return buf;
}