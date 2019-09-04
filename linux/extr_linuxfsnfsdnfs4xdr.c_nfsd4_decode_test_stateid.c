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
struct nfsd4_test_stateid_id {int /*<<< orphan*/  ts_id_stateid; int /*<<< orphan*/  ts_id_list; } ;
struct nfsd4_test_stateid {int ts_num_ids; int /*<<< orphan*/  ts_stateid_list; } ;
struct nfsd4_compoundargs {int dummy; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  READ_BUF (int) ; 
 int /*<<< orphan*/  dprintk (char*,char*,int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ nfsd4_decode_stateid (struct nfsd4_compoundargs*,int /*<<< orphan*/ *) ; 
 scalar_t__ nfserr_bad_xdr ; 
 scalar_t__ nfserrno (int /*<<< orphan*/ ) ; 
 int ntohl (int /*<<< orphan*/ ) ; 
 struct nfsd4_test_stateid_id* svcxdr_tmpalloc (struct nfsd4_compoundargs*,int) ; 

__attribute__((used)) static __be32
nfsd4_decode_test_stateid(struct nfsd4_compoundargs *argp, struct nfsd4_test_stateid *test_stateid)
{
	int i;
	__be32 *p, status;
	struct nfsd4_test_stateid_id *stateid;

	READ_BUF(4);
	test_stateid->ts_num_ids = ntohl(*p++);

	INIT_LIST_HEAD(&test_stateid->ts_stateid_list);

	for (i = 0; i < test_stateid->ts_num_ids; i++) {
		stateid = svcxdr_tmpalloc(argp, sizeof(*stateid));
		if (!stateid) {
			status = nfserrno(-ENOMEM);
			goto out;
		}

		INIT_LIST_HEAD(&stateid->ts_id_list);
		list_add_tail(&stateid->ts_id_list, &test_stateid->ts_stateid_list);

		status = nfsd4_decode_stateid(argp, &stateid->ts_id_stateid);
		if (status)
			goto out;
	}

	status = 0;
out:
	return status;
xdr_error:
	dprintk("NFSD: xdr error (%s:%d)\n", __FILE__, __LINE__);
	status = nfserr_bad_xdr;
	goto out;
}