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
struct nfsd_file {int /*<<< orphan*/  nf_flags; int /*<<< orphan*/  nf_ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFSD_FILE_HASHED ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int atomic_dec_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfsd_file_free (struct nfsd_file*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_nfsd_file_put (struct nfsd_file*) ; 

__attribute__((used)) static int
nfsd_file_put_noref(struct nfsd_file *nf)
{
	int count;
	trace_nfsd_file_put(nf);

	count = atomic_dec_return(&nf->nf_ref);
	if (!count) {
		WARN_ON(test_bit(NFSD_FILE_HASHED, &nf->nf_flags));
		nfsd_file_free(nf);
	}
	return count;
}