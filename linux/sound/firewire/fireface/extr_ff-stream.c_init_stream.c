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
struct fw_iso_resources {int dummy; } ;
struct amdtp_stream {int dummy; } ;
struct snd_ff {int /*<<< orphan*/  unit; struct fw_iso_resources rx_resources; struct fw_iso_resources tx_resources; struct amdtp_stream tx_stream; } ;
typedef  enum amdtp_stream_direction { ____Placeholder_amdtp_stream_direction } amdtp_stream_direction ;

/* Variables and functions */
 int AMDTP_IN_STREAM ; 
 int AMDTP_OUT_STREAM ; 
 int amdtp_ff_init (struct amdtp_stream*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fw_iso_resources_destroy (struct fw_iso_resources*) ; 
 int fw_iso_resources_init (struct fw_iso_resources*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int init_stream(struct snd_ff *ff, struct amdtp_stream *s)
{
	struct fw_iso_resources *resources;
	enum amdtp_stream_direction dir;
	int err;

	if (s == &ff->tx_stream) {
		resources = &ff->tx_resources;
		dir = AMDTP_IN_STREAM;
	} else {
		resources = &ff->rx_resources;
		dir = AMDTP_OUT_STREAM;
	}

	err = fw_iso_resources_init(resources, ff->unit);
	if (err < 0)
		return err;

	err = amdtp_ff_init(s, ff->unit, dir);
	if (err < 0)
		fw_iso_resources_destroy(resources);

	return err;
}