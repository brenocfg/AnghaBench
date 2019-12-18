#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct tagMSIVIEW {int dummy; } ;
typedef  size_t UINT ;
struct TYPE_9__ {scalar_t__ QuadPart; } ;
struct TYPE_8__ {TYPE_2__* db; } ;
struct TYPE_7__ {size_t num_streams; TYPE_1__* streams; } ;
struct TYPE_6__ {int /*<<< orphan*/ * stream; } ;
typedef  TYPE_3__ MSISTREAMSVIEW ;
typedef  TYPE_4__ LARGE_INTEGER ;
typedef  int /*<<< orphan*/  IStream ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 size_t ERROR_FUNCTION_FAILED ; 
 size_t ERROR_SUCCESS ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IStream_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IStream_Seek (int /*<<< orphan*/ *,TYPE_4__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STREAM_SEEK_SET ; 
 int /*<<< orphan*/  TRACE (char*,struct tagMSIVIEW*,size_t,size_t,int /*<<< orphan*/ **) ; 

__attribute__((used)) static UINT STREAMS_fetch_stream(struct tagMSIVIEW *view, UINT row, UINT col, IStream **stm)
{
    MSISTREAMSVIEW *sv = (MSISTREAMSVIEW *)view;
    LARGE_INTEGER pos;
    HRESULT hr;

    TRACE("(%p, %d, %d, %p)\n", view, row, col, stm);

    if (row >= sv->db->num_streams)
        return ERROR_FUNCTION_FAILED;

    pos.QuadPart = 0;
    hr = IStream_Seek( sv->db->streams[row].stream, pos, STREAM_SEEK_SET, NULL );
    if (FAILED( hr ))
        return ERROR_FUNCTION_FAILED;

    *stm = sv->db->streams[row].stream;
    IStream_AddRef( *stm );

    return ERROR_SUCCESS;
}