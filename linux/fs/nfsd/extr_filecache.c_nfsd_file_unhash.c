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
struct nfsd_file {int /*<<< orphan*/  nf_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFSD_FILE_HASHED ; 
 int /*<<< orphan*/  nfsd_file_do_unhash (struct nfsd_file*) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
nfsd_file_unhash(struct nfsd_file *nf)
{
	if (test_and_clear_bit(NFSD_FILE_HASHED, &nf->nf_flags)) {
		nfsd_file_do_unhash(nf);
		return true;
	}
	return false;
}