#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  (* seek_fn ) (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  error; } ;
typedef  int /*<<< orphan*/  HPDF_WhenceMode ;
typedef  TYPE_1__* HPDF_Stream ;
typedef  int /*<<< orphan*/  HPDF_STATUS ;
typedef  int /*<<< orphan*/  HPDF_INT ;

/* Variables and functions */
 scalar_t__ HPDF_Error_GetCode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_INVALID_OPERATION ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 
 int /*<<< orphan*/  HPDF_SetError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_THIS_FUNC_WAS_SKIPPED ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

HPDF_STATUS
HPDF_Stream_Seek  (HPDF_Stream      stream,
                   HPDF_INT         pos,
                   HPDF_WhenceMode  mode)
{
    HPDF_PTRACE((" HPDF_Stream_Seek\n"));

    if (!(stream->seek_fn))
        return HPDF_SetError (stream->error, HPDF_INVALID_OPERATION, 0);

    if (HPDF_Error_GetCode(stream->error) != 0)
        return HPDF_THIS_FUNC_WAS_SKIPPED;

    return stream->seek_fn(stream, pos, mode);
}