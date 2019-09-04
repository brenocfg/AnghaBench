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
struct xdr_netobj {int dummy; } ;
struct svc_rqst {int dummy; } ;
struct rsc {int /*<<< orphan*/  h; int /*<<< orphan*/  mechctx; } ;
struct cache_detail {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GSS_SEQ_WIN ; 
 int GSS_S_COMPLETE ; 
 int GSS_S_NO_CONTEXT ; 
 int /*<<< orphan*/  cache_put (int /*<<< orphan*/ *,struct cache_detail*) ; 
 struct rsc* gss_svc_searchbyctx (struct cache_detail*,struct xdr_netobj*) ; 
 int gss_write_null_verf (struct svc_rqst*) ; 
 int gss_write_verf (struct svc_rqst*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
gss_write_init_verf(struct cache_detail *cd, struct svc_rqst *rqstp,
		struct xdr_netobj *out_handle, int *major_status)
{
	struct rsc *rsci;
	int        rc;

	if (*major_status != GSS_S_COMPLETE)
		return gss_write_null_verf(rqstp);
	rsci = gss_svc_searchbyctx(cd, out_handle);
	if (rsci == NULL) {
		*major_status = GSS_S_NO_CONTEXT;
		return gss_write_null_verf(rqstp);
	}
	rc = gss_write_verf(rqstp, rsci->mechctx, GSS_SEQ_WIN);
	cache_put(&rsci->h, cd);
	return rc;
}