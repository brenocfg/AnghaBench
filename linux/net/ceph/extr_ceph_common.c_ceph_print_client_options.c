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
struct seq_file {size_t count; } ;
struct ceph_options {int flags; scalar_t__ mount_timeout; scalar_t__ osd_idle_ttl; scalar_t__ osd_keepalive_timeout; scalar_t__ osd_request_timeout; int /*<<< orphan*/  fsid; scalar_t__ key; scalar_t__ name; } ;
struct ceph_client {struct ceph_options* options; } ;

/* Variables and functions */
 scalar_t__ CEPH_MOUNT_TIMEOUT_DEFAULT ; 
 int CEPH_OPT_ABORT_ON_FULL ; 
 int CEPH_OPT_FSID ; 
 int CEPH_OPT_NOCRC ; 
 int CEPH_OPT_NOMSGAUTH ; 
 int CEPH_OPT_NOMSGSIGN ; 
 int CEPH_OPT_NOSHARE ; 
 int CEPH_OPT_TCP_NODELAY ; 
 scalar_t__ CEPH_OSD_IDLE_TTL_DEFAULT ; 
 scalar_t__ CEPH_OSD_KEEPALIVE_DEFAULT ; 
 scalar_t__ CEPH_OSD_REQUEST_TIMEOUT_DEFAULT ; 
 int jiffies_to_msecs (scalar_t__) ; 
 int /*<<< orphan*/  seq_escape (struct seq_file*,scalar_t__,char*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int) ; 
 int /*<<< orphan*/  seq_putc (struct seq_file*,char) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

int ceph_print_client_options(struct seq_file *m, struct ceph_client *client,
			      bool show_all)
{
	struct ceph_options *opt = client->options;
	size_t pos = m->count;

	if (opt->name) {
		seq_puts(m, "name=");
		seq_escape(m, opt->name, ", \t\n\\");
		seq_putc(m, ',');
	}
	if (opt->key)
		seq_puts(m, "secret=<hidden>,");

	if (opt->flags & CEPH_OPT_FSID)
		seq_printf(m, "fsid=%pU,", &opt->fsid);
	if (opt->flags & CEPH_OPT_NOSHARE)
		seq_puts(m, "noshare,");
	if (opt->flags & CEPH_OPT_NOCRC)
		seq_puts(m, "nocrc,");
	if (opt->flags & CEPH_OPT_NOMSGAUTH)
		seq_puts(m, "nocephx_require_signatures,");
	if (opt->flags & CEPH_OPT_NOMSGSIGN)
		seq_puts(m, "nocephx_sign_messages,");
	if ((opt->flags & CEPH_OPT_TCP_NODELAY) == 0)
		seq_puts(m, "notcp_nodelay,");
	if (show_all && (opt->flags & CEPH_OPT_ABORT_ON_FULL))
		seq_puts(m, "abort_on_full,");

	if (opt->mount_timeout != CEPH_MOUNT_TIMEOUT_DEFAULT)
		seq_printf(m, "mount_timeout=%d,",
			   jiffies_to_msecs(opt->mount_timeout) / 1000);
	if (opt->osd_idle_ttl != CEPH_OSD_IDLE_TTL_DEFAULT)
		seq_printf(m, "osd_idle_ttl=%d,",
			   jiffies_to_msecs(opt->osd_idle_ttl) / 1000);
	if (opt->osd_keepalive_timeout != CEPH_OSD_KEEPALIVE_DEFAULT)
		seq_printf(m, "osdkeepalivetimeout=%d,",
		    jiffies_to_msecs(opt->osd_keepalive_timeout) / 1000);
	if (opt->osd_request_timeout != CEPH_OSD_REQUEST_TIMEOUT_DEFAULT)
		seq_printf(m, "osd_request_timeout=%d,",
			   jiffies_to_msecs(opt->osd_request_timeout) / 1000);

	/* drop redundant comma */
	if (m->count != pos)
		m->count--;

	return 0;
}