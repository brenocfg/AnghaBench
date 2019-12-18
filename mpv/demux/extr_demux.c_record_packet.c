#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mp_recorder_sink {int dummy; } ;
struct demux_packet {size_t stream; } ;
struct demux_internal {int enable_recording; scalar_t__ dumper_status; int /*<<< orphan*/ * recorder; int /*<<< orphan*/ * streams; TYPE_1__* opts; } ;
struct TYPE_2__ {scalar_t__* record_file; } ;

/* Variables and functions */
 scalar_t__ CONTROL_OK ; 
 int /*<<< orphan*/  MP_ERR (struct demux_internal*,char*) ; 
 int /*<<< orphan*/  mp_recorder_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_recorder_feed_packet (struct mp_recorder_sink*,struct demux_packet*) ; 
 struct mp_recorder_sink* mp_recorder_get_sink (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * recorder_create (struct demux_internal*,scalar_t__*) ; 
 int /*<<< orphan*/  write_dump_packet (struct demux_internal*,struct demux_packet*) ; 

__attribute__((used)) static void record_packet(struct demux_internal *in, struct demux_packet *dp)
{
    // (should preferably be outside of the lock)
    if (in->enable_recording && !in->recorder &&
        in->opts->record_file && in->opts->record_file[0])
    {
        // Later failures shouldn't make it retry and overwrite the previously
        // recorded file.
        in->enable_recording = false;

        in->recorder = recorder_create(in, in->opts->record_file);
        if (!in->recorder)
            MP_ERR(in, "Disabling recording.\n");
    }

    if (in->recorder) {
        struct mp_recorder_sink *sink =
            mp_recorder_get_sink(in->recorder, in->streams[dp->stream]);
        if (sink) {
            mp_recorder_feed_packet(sink, dp);
        } else {
            MP_ERR(in, "New stream appeared; stopping recording.\n");
            mp_recorder_destroy(in->recorder);
            in->recorder = NULL;
        }
    }

    if (in->dumper_status == CONTROL_OK)
        write_dump_packet(in, dp);
}