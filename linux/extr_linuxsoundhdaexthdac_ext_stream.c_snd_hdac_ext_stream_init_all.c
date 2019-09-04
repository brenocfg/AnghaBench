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
struct hdac_ext_stream {int dummy; } ;
struct hdac_bus {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct hdac_ext_stream* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hdac_ext_stream_init (struct hdac_bus*,struct hdac_ext_stream*,int,int,int) ; 

int snd_hdac_ext_stream_init_all(struct hdac_bus *bus, int start_idx,
		int num_stream, int dir)
{
	int stream_tag = 0;
	int i, tag, idx = start_idx;

	for (i = 0; i < num_stream; i++) {
		struct hdac_ext_stream *stream =
				kzalloc(sizeof(*stream), GFP_KERNEL);
		if (!stream)
			return -ENOMEM;
		tag = ++stream_tag;
		snd_hdac_ext_stream_init(bus, stream, idx, dir, tag);
		idx++;
	}

	return 0;

}