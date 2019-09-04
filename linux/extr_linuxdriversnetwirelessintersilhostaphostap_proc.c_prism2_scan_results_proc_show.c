#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned char u8 ;
struct seq_file {int /*<<< orphan*/  file; } ;
struct hfa384x_hostscan_result {unsigned char* sup_rates; unsigned char* ssid; int /*<<< orphan*/  ssid_len; int /*<<< orphan*/  atim; int /*<<< orphan*/  bssid; int /*<<< orphan*/  rate; int /*<<< orphan*/  capability; int /*<<< orphan*/  beacon_interval; int /*<<< orphan*/  sl; int /*<<< orphan*/  anl; int /*<<< orphan*/  chid; } ;
typedef  int /*<<< orphan*/  s16 ;
struct TYPE_3__ {struct hfa384x_hostscan_result* last_scan_results; } ;
typedef  TYPE_1__ local_info_t ;

/* Variables and functions */
 TYPE_1__* PDE_DATA (int /*<<< orphan*/ ) ; 
 void* SEQ_START_TOKEN ; 
 int /*<<< orphan*/  file_inode (int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 
 int /*<<< orphan*/  seq_putc (struct seq_file*,char) ; 

__attribute__((used)) static int prism2_scan_results_proc_show(struct seq_file *m, void *v)
{
	local_info_t *local = PDE_DATA(file_inode(m->file));
	unsigned long entry;
	int i, len;
	struct hfa384x_hostscan_result *scanres;
	u8 *p;

	if (v == SEQ_START_TOKEN) {
		seq_printf(m,
			   "CHID ANL SL BcnInt Capab Rate BSSID ATIM SupRates SSID\n");
		return 0;
	}

	entry = (unsigned long)v - 2;
	scanres = &local->last_scan_results[entry];

	seq_printf(m, "%d %d %d %d 0x%02x %d %pM %d ",
		   le16_to_cpu(scanres->chid),
		   (s16) le16_to_cpu(scanres->anl),
		   (s16) le16_to_cpu(scanres->sl),
		   le16_to_cpu(scanres->beacon_interval),
		   le16_to_cpu(scanres->capability),
		   le16_to_cpu(scanres->rate),
		   scanres->bssid,
		   le16_to_cpu(scanres->atim));

	p = scanres->sup_rates;
	for (i = 0; i < sizeof(scanres->sup_rates); i++) {
		if (p[i] == 0)
			break;
		seq_printf(m, "<%02x>", p[i]);
	}
	seq_putc(m, ' ');

	p = scanres->ssid;
	len = le16_to_cpu(scanres->ssid_len);
	if (len > 32)
		len = 32;
	for (i = 0; i < len; i++) {
		unsigned char c = p[i];
		if (c >= 32 && c < 127)
			seq_putc(m, c);
		else
			seq_printf(m, "<%02x>", c);
	}
	seq_putc(m, '\n');
	return 0;
}