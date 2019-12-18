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
 int /*<<< orphan*/  NFSD_FILE_LAUNDRETTE_MAY_FLUSH ; 
 int /*<<< orphan*/  NFSD_FILE_REFERENCED ; 
 int /*<<< orphan*/  nfsd_file_in_use (struct nfsd_file*) ; 
 int nfsd_file_put_noref (struct nfsd_file*) ; 
 int /*<<< orphan*/  nfsd_file_schedule_laundrette (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
nfsd_file_put(struct nfsd_file *nf)
{
	bool is_hashed = test_bit(NFSD_FILE_HASHED, &nf->nf_flags) != 0;
	bool unused = !nfsd_file_in_use(nf);

	set_bit(NFSD_FILE_REFERENCED, &nf->nf_flags);
	if (nfsd_file_put_noref(nf) == 1 && is_hashed && unused)
		nfsd_file_schedule_laundrette(NFSD_FILE_LAUNDRETTE_MAY_FLUSH);
}