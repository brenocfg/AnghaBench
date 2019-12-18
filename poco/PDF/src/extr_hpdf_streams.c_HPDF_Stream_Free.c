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
struct TYPE_5__ {int /*<<< orphan*/  mmgr; scalar_t__ sig_bytes; int /*<<< orphan*/  (* free_fn ) (TYPE_1__*) ;} ;
typedef  TYPE_1__* HPDF_Stream ;

/* Variables and functions */
 int /*<<< orphan*/  HPDF_FreeMem (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

void
HPDF_Stream_Free  (HPDF_Stream  stream)
{
    if (!stream)
        return;

    if (stream->free_fn)
        stream->free_fn(stream);

    stream->sig_bytes = 0;

    HPDF_FreeMem(stream->mmgr, stream);
}