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
struct snd_motu_protocol {scalar_t__ (* get_clock_rate ) (struct snd_motu*,unsigned int*) ;scalar_t__ (* get_clock_source ) (struct snd_motu*,int*) ;} ;
struct snd_motu {TYPE_1__* spec; } ;
struct snd_info_entry {struct snd_motu* private_data; } ;
struct snd_info_buffer {int dummy; } ;
typedef  enum snd_motu_clock_source { ____Placeholder_snd_motu_clock_source } snd_motu_clock_source ;
struct TYPE_2__ {struct snd_motu_protocol* protocol; } ;

/* Variables and functions */
 unsigned int* clock_names ; 
 int /*<<< orphan*/  snd_iprintf (struct snd_info_buffer*,char*,unsigned int) ; 
 scalar_t__ stub1 (struct snd_motu*,unsigned int*) ; 
 scalar_t__ stub2 (struct snd_motu*,int*) ; 

__attribute__((used)) static void proc_read_clock(struct snd_info_entry *entry,
			    struct snd_info_buffer *buffer)
{

	struct snd_motu *motu = entry->private_data;
	const struct snd_motu_protocol *const protocol = motu->spec->protocol;
	unsigned int rate;
	enum snd_motu_clock_source source;

	if (protocol->get_clock_rate(motu, &rate) < 0)
		return;
	if (protocol->get_clock_source(motu, &source) < 0)
		return;

	snd_iprintf(buffer, "Rate:\t%d\n", rate);
	snd_iprintf(buffer, "Source:\t%s\n", clock_names[source]);
}