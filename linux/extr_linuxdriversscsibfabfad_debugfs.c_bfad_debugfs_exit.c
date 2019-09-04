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
struct bfad_s {int /*<<< orphan*/ ** bfad_dentry_files; } ;
struct bfad_port_s {int /*<<< orphan*/ * port_debugfs_root; struct bfad_s* bfad; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_debugfs_port_count ; 
 int /*<<< orphan*/ * bfa_debugfs_root ; 
 int /*<<< orphan*/  bfad_debugfs_files ; 
 int /*<<< orphan*/  debugfs_remove (int /*<<< orphan*/ *) ; 

inline void
bfad_debugfs_exit(struct bfad_port_s *port)
{
	struct bfad_s *bfad = port->bfad;
	int i;

	for (i = 0; i < ARRAY_SIZE(bfad_debugfs_files); i++) {
		if (bfad->bfad_dentry_files[i]) {
			debugfs_remove(bfad->bfad_dentry_files[i]);
			bfad->bfad_dentry_files[i] = NULL;
		}
	}

	/* Remove the pci_dev debugfs directory for the port */
	if (port->port_debugfs_root) {
		debugfs_remove(port->port_debugfs_root);
		port->port_debugfs_root = NULL;
		atomic_dec(&bfa_debugfs_port_count);
	}

	/* Remove the BFA debugfs root directory */
	if (atomic_read(&bfa_debugfs_port_count) == 0) {
		debugfs_remove(bfa_debugfs_root);
		bfa_debugfs_root = NULL;
	}
}