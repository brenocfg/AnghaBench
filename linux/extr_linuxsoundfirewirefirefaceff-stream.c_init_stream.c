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
struct amdtp_stream {int dummy; } ;
struct fw_iso_resources {int dummy; } ;
struct snd_ff {int /*<<< orphan*/  unit; struct amdtp_stream rx_stream; struct fw_iso_resources rx_resources; struct amdtp_stream tx_stream; struct fw_iso_resources tx_resources; } ;
typedef  enum amdtp_stream_direction { ____Placeholder_amdtp_stream_direction } amdtp_stream_direction ;

/* Variables and functions */
 int AMDTP_IN_STREAM ; 
 int amdtp_ff_init (struct amdtp_stream*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fw_iso_resources_destroy (struct fw_iso_resources*) ; 
 int fw_iso_resources_init (struct fw_iso_resources*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int init_stream(struct snd_ff *ff, enum amdtp_stream_direction dir)
{
	int err;
	struct fw_iso_resources *resources;
	struct amdtp_stream *stream;

	if (dir == AMDTP_IN_STREAM) {
		resources = &ff->tx_resources;
		stream = &ff->tx_stream;
	} else {
		resources = &ff->rx_resources;
		stream = &ff->rx_stream;
	}

	err = fw_iso_resources_init(resources, ff->unit);
	if (err < 0)
		return err;

	err = amdtp_ff_init(stream, ff->unit, dir);
	if (err < 0)
		fw_iso_resources_destroy(resources);

	return err;
}