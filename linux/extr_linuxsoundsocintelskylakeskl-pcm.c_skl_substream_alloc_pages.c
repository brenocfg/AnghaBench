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
struct snd_pcm_substream {int dummy; } ;
struct hdac_ext_stream {int dummy; } ;
struct hdac_bus {int dummy; } ;
struct TYPE_2__ {scalar_t__ format_val; scalar_t__ period_bytes; scalar_t__ bufsize; } ;

/* Variables and functions */
 struct hdac_ext_stream* get_hdac_ext_stream (struct snd_pcm_substream*) ; 
 TYPE_1__* hdac_stream (struct hdac_ext_stream*) ; 
 int snd_pcm_lib_malloc_pages (struct snd_pcm_substream*,size_t) ; 

__attribute__((used)) static int skl_substream_alloc_pages(struct hdac_bus *bus,
				 struct snd_pcm_substream *substream,
				 size_t size)
{
	struct hdac_ext_stream *stream = get_hdac_ext_stream(substream);

	hdac_stream(stream)->bufsize = 0;
	hdac_stream(stream)->period_bytes = 0;
	hdac_stream(stream)->format_val = 0;

	return snd_pcm_lib_malloc_pages(substream, size);
}