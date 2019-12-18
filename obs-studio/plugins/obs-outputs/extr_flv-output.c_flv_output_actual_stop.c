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
struct flv_output {int /*<<< orphan*/  output; scalar_t__ file; int /*<<< orphan*/  last_packet_ts; int /*<<< orphan*/  active; } ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (scalar_t__) ; 
 int /*<<< orphan*/  info (char*) ; 
 int /*<<< orphan*/  obs_output_end_data_capture (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_output_signal_stop (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  os_atomic_set_bool (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  os_ftelli64 (scalar_t__) ; 
 int /*<<< orphan*/  write_file_info (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void flv_output_actual_stop(struct flv_output *stream, int code)
{
	os_atomic_set_bool(&stream->active, false);

	if (stream->file) {
		write_file_info(stream->file, stream->last_packet_ts,
				os_ftelli64(stream->file));

		fclose(stream->file);
	}
	if (code) {
		obs_output_signal_stop(stream->output, code);
	} else {
		obs_output_end_data_capture(stream->output);
	}

	info("FLV file output complete");
}