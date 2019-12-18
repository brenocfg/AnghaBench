#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct thread_args {int stream; TYPE_4__* This; } ;
struct TYPE_11__ {int cStreams; TYPE_1__* pInputPin; } ;
struct TYPE_13__ {TYPE_3__* streams; TYPE_2__ Parser; } ;
struct TYPE_12__ {scalar_t__ index_next; scalar_t__ index; scalar_t__ entries; int /*<<< orphan*/ * thread; scalar_t__ stdindex; int /*<<< orphan*/  seek; int /*<<< orphan*/  pos; int /*<<< orphan*/  pos_next; int /*<<< orphan*/  packet_queued; } ;
struct TYPE_10__ {int /*<<< orphan*/  pReader; } ;
typedef  TYPE_3__ StreamData ;
typedef  TYPE_4__* LPVOID ;
typedef  int /*<<< orphan*/  IMediaSample ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DWORD_PTR ;
typedef  int DWORD ;
typedef  int BOOL ;
typedef  TYPE_4__ AVISplitterImpl ;

/* Variables and functions */
 int /*<<< orphan*/  AVISplitter_Sample (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AVISplitter_SendEndOfFile (TYPE_4__*,int) ; 
 int /*<<< orphan*/  AVISplitter_next_request (TYPE_4__*,int) ; 
 int /*<<< orphan*/  AVISplitter_thread_reader ; 
 struct thread_args* CoTaskMemAlloc (int) ; 
 int /*<<< orphan*/ * CreateThread (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct thread_args*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int FALSE ; 
 int /*<<< orphan*/  IAsyncReader_WaitForNext (int /*<<< orphan*/ ,int,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IMediaSample_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ResetEvent (int /*<<< orphan*/ ) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_FALSE ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VFW_E_NOT_CONNECTED ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static HRESULT AVISplitter_first_request(LPVOID iface)
{
    AVISplitterImpl *This = iface;
    HRESULT hr = S_OK;
    DWORD x;
    IMediaSample *sample = NULL;
    BOOL have_sample = FALSE;

    TRACE("(%p)->()\n", This);

    for (x = 0; x < This->Parser.cStreams; ++x)
    {
        StreamData *stream = This->streams + x;

        /* Nothing should be running at this point */
        assert(!stream->thread);

        assert(!sample);
        /* It could be we asked the thread to terminate, and the thread
         * already terminated before receiving the deathwish */
        ResetEvent(stream->packet_queued);

        stream->pos_next = stream->pos;
        stream->index_next = stream->index;

        /* This was sent after stopped->paused or stopped->playing, so set seek */
        stream->seek = TRUE;

        /* There should be a packet queued from AVISplitter_next_request last time
         * It needs to be done now because this is the only way to ensure that every
         * stream will have at least 1 packet processed
         * If this is done after the threads start it could go all awkward and we
         * would have no guarantees that it's successful at all
         */

        if (have_sample)
        {
            DWORD_PTR dwUser = ~0;
            hr = IAsyncReader_WaitForNext(This->Parser.pInputPin->pReader, 10000, &sample, &dwUser);
            assert(hr == S_OK);
            assert(sample);

            AVISplitter_Sample(iface, sample, dwUser);
            IMediaSample_Release(sample);
        }

        hr = AVISplitter_next_request(This, x);
        TRACE("-->%08x\n", hr);

        /* Could be an EOF instead */
        have_sample = (hr == S_OK);
        if (hr == S_FALSE)
            AVISplitter_SendEndOfFile(This, x);

        if (FAILED(hr) && hr != VFW_E_NOT_CONNECTED)
            break;
        hr = S_OK;
    }

    /* FIXME: Don't do this for each pin that sent an EOF */
    for (x = 0; x < This->Parser.cStreams && SUCCEEDED(hr); ++x)
    {
        struct thread_args *args;
        DWORD tid;

        if ((This->streams[x].stdindex && This->streams[x].index_next >= This->streams[x].entries) ||
            (!This->streams[x].stdindex && This->streams[x].index_next))
        {
            This->streams[x].thread = NULL;
            continue;
        }

        args = CoTaskMemAlloc(sizeof(*args));
        args->This = This;
        args->stream = x;
        This->streams[x].thread = CreateThread(NULL, 0, AVISplitter_thread_reader, args, 0, &tid);
        TRACE("Created stream %u thread 0x%08x\n", x, tid);
    }

    if (FAILED(hr))
        ERR("Horsemen of the apocalypse came to bring error 0x%08x\n", hr);

    return hr;
}