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
struct TYPE_5__ {struct TYPE_5__* dictCtx; } ;
struct TYPE_6__ {TYPE_1__ internal_donotuse; } ;
typedef  TYPE_2__ LZ4_streamHC_t ;

/* Variables and functions */

void LZ4_attach_HC_dictionary(LZ4_streamHC_t *working_stream, const LZ4_streamHC_t *dictionary_stream) {
    working_stream->internal_donotuse.dictCtx = dictionary_stream != NULL ? &(dictionary_stream->internal_donotuse) : NULL;
}