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
struct TYPE_4__ {scalar_t__ (* write_fn ) (TYPE_1__*,int /*<<< orphan*/  const*,scalar_t__) ;int /*<<< orphan*/  size; int /*<<< orphan*/  error; } ;
typedef  scalar_t__ HPDF_UINT ;
typedef  TYPE_1__* HPDF_Stream ;
typedef  scalar_t__ HPDF_STATUS ;
typedef  int /*<<< orphan*/  HPDF_BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  HPDF_INVALID_OPERATION ; 
 scalar_t__ HPDF_OK ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 
 scalar_t__ HPDF_SetError (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (TYPE_1__*,int /*<<< orphan*/  const*,scalar_t__) ; 

HPDF_STATUS
HPDF_Stream_Write  (HPDF_Stream      stream,
                    const HPDF_BYTE  *ptr,
                    HPDF_UINT        size)
{
    HPDF_STATUS ret;

    HPDF_PTRACE((" HPDF_Stream_Write\n"));

    if (!(stream->write_fn))
        return HPDF_SetError(stream->error, HPDF_INVALID_OPERATION, 0);

    /*
    if (HPDF_Error_GetCode(stream->error) != HPDF_NOERROR)
        return HPDF_THIS_FUNC_WAS_SKIPPED;
    */

    ret = stream->write_fn(stream, ptr, size);

    if (ret != HPDF_OK)
        return ret;

    stream->size += size;

    return HPDF_OK;
}