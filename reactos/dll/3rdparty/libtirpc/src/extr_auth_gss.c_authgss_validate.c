#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
struct TYPE_9__ {scalar_t__ qop; } ;
struct TYPE_8__ {scalar_t__ gc_proc; int /*<<< orphan*/  gc_seq; } ;
struct TYPE_7__ {int length; int /*<<< orphan*/ * value; } ;
struct rpc_gss_data {scalar_t__ established; TYPE_3__ sec; int /*<<< orphan*/  ctx; TYPE_2__ gc; int /*<<< orphan*/  win; TYPE_1__ gc_wire_verf; } ;
struct opaque_auth {int oa_length; scalar_t__* oa_base; } ;
typedef  int /*<<< orphan*/  num ;
struct TYPE_10__ {scalar_t__* value; int length; } ;
typedef  TYPE_4__ gss_buffer_desc ;
typedef  scalar_t__ bool_t ;
typedef  scalar_t__ OM_uint32 ;
typedef  int /*<<< orphan*/  AUTH ;

/* Variables and functions */
 struct rpc_gss_data* AUTH_PRIVATE (int /*<<< orphan*/ *) ; 
 scalar_t__ FALSE ; 
 scalar_t__ GSS_S_COMPLETE ; 
 scalar_t__ GSS_S_CONTEXT_EXPIRED ; 
 scalar_t__ RPCSEC_GSS_CONTINUE_INIT ; 
 scalar_t__ RPCSEC_GSS_INIT ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  authgss_destroy_context (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ gss_verify_mic (scalar_t__*,int /*<<< orphan*/ ,TYPE_4__*,TYPE_4__*,scalar_t__*) ; 
 scalar_t__ htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_debug (char*) ; 
 int /*<<< orphan*/  log_status (char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/ * mem_alloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__*,int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static bool_t
authgss_validate(AUTH *auth, struct opaque_auth *verf)
{
	struct rpc_gss_data	*gd;
	u_int			 num, qop_state;
	gss_buffer_desc		 signbuf, checksum;
	OM_uint32		 maj_stat, min_stat;

	log_debug("in authgss_validate()");

	gd = AUTH_PRIVATE(auth);

	if (gd->established == FALSE) {
		/* would like to do this only on NULL rpc --
		 * gc->established is good enough.
		 * save the on the wire verifier to validate last
		 * INIT phase packet after decode if the major
		 * status is GSS_S_COMPLETE
		 */
		if ((gd->gc_wire_verf.value =
				mem_alloc(verf->oa_length)) == NULL) {
			fprintf(stderr, "gss_validate: out of memory\n");
			return (FALSE);
		}
		memcpy(gd->gc_wire_verf.value, verf->oa_base, verf->oa_length);
		gd->gc_wire_verf.length = verf->oa_length;
		return (TRUE);
  	}

	if (gd->gc.gc_proc == RPCSEC_GSS_INIT ||
	    gd->gc.gc_proc == RPCSEC_GSS_CONTINUE_INIT) {
		num = htonl(gd->win);
	}
	else num = htonl(gd->gc.gc_seq);

	signbuf.value = &num;
	signbuf.length = sizeof(num);

	checksum.value = verf->oa_base;
	checksum.length = verf->oa_length;

	maj_stat = gss_verify_mic(&min_stat, gd->ctx, &signbuf,
				  &checksum, &qop_state);
	if (maj_stat != GSS_S_COMPLETE || qop_state != gd->sec.qop) {
		log_status("gss_verify_mic", maj_stat, min_stat);
		if (maj_stat == GSS_S_CONTEXT_EXPIRED) {
			gd->established = FALSE;
			authgss_destroy_context(auth);
		}
		return (FALSE);
	}
	return (TRUE);
}