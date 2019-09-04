#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snd_info_private_data {TYPE_3__* rbuffer; struct snd_info_entry* entry; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* read ) (struct snd_info_entry*,TYPE_3__*) ;} ;
struct TYPE_5__ {TYPE_1__ text; } ;
struct snd_info_entry {TYPE_2__ c; } ;
struct seq_file {struct snd_info_private_data* private; } ;
struct TYPE_6__ {char* buffer; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  stub1 (struct snd_info_entry*,TYPE_3__*) ; 

__attribute__((used)) static int snd_info_seq_show(struct seq_file *seq, void *p)
{
	struct snd_info_private_data *data = seq->private;
	struct snd_info_entry *entry = data->entry;

	if (!entry->c.text.read) {
		return -EIO;
	} else {
		data->rbuffer->buffer = (char *)seq; /* XXX hack! */
		entry->c.text.read(entry, data->rbuffer);
	}
	return 0;
}