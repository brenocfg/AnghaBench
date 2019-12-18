#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_info_entry {struct snd_ff* private_data; } ;
struct snd_info_buffer {int dummy; } ;
struct snd_ff {TYPE_2__* spec; } ;
struct TYPE_4__ {TYPE_1__* protocol; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* dump_status ) (struct snd_ff*,struct snd_info_buffer*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct snd_ff*,struct snd_info_buffer*) ; 

__attribute__((used)) static void proc_dump_status(struct snd_info_entry *entry,
			     struct snd_info_buffer *buffer)
{
	struct snd_ff *ff = entry->private_data;

	ff->spec->protocol->dump_status(ff, buffer);
}